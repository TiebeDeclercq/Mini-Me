import 'package:flutter/material.dart';
import 'package:mini_me/services/udp_service.dart';

class InteractScreen extends StatefulWidget {
  const InteractScreen({super.key});

  @override
  State<InteractScreen> createState() => _InteractScreenState();
}

class _InteractScreenState extends State<InteractScreen> {
  late UdpService _udpService;
  bool _isInitialized = false;
  bool _isSending = false;

  final List<Map<String, dynamic>> _servos = List.generate(
    19,
    (index) => {
      'id': index,
      'angle': 90,
      'name': 'Servo ${index + 1}',
    },
  );

  @override
  void initState() {
    super.initState();
    _udpService = UdpService(
      port: 5005,
      address: '',
    );
    _initializeUdp();
  }

  /// Initialiseert de UDP-verbinding
  Future<void> _initializeUdp() async {
    try {
      await _udpService.initializeUDP();
      setState(() {
        _isInitialized = true;
      });
    } catch (e) {
      print('Fout bij het initialiseren van UDP: $e');
    }
  }

  /// Verzendt een reset-opdracht naar alle servos
  Future<void> _sendServoReset() async {
    if (!_isInitialized || _isSending) return;

    setState(() {
      _isSending = true;
    });

    try {
      // Maak de servos array met alle servos ingesteld op 90 graden
      final servosArray = List.generate(
          19,
          (index) => {
                'id': index,
                'angle': 90,
              });

      // Verzend de opdracht in het gespecificeerde formaat
      await _udpService.sendMultipleServoCommands(servosArray);

      // Werk de UI bij om de nieuwe posities weer te geven
      setState(() {
        for (var servo in _servos) {
          servo['angle'] = 90;
        }
      });

      ScaffoldMessenger.of(context).showSnackBar(
        const SnackBar(content: Text('Reset uitgevoerd')),
      );
    } catch (error) {
      print('Fout bij het verzenden van de reset-opdracht: $error');
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(content: Text('Fout: $error')),
      );
    } finally {
      setState(() {
        _isSending = false;
      });
    }
  }

  /// Selecteert een animatie en verzendt de opdracht
  Future<void> _selectAnimation(int animationId) async {
    if (!_isInitialized || _isSending) return;

    setState(() {
      _isSending = true;
    });

    try {
      // Verzend animatie selectie opdracht
      final message = {'animation': animationId};
      await _udpService.sendMessage(message);
    } finally {
      setState(() {
        _isSending = false;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Mini-Me'),
        leading: IconButton(
          icon: const Icon(Icons.menu),
          onPressed: () => Scaffold.of(context).openDrawer(),
        ),
      ),
      body: !_isInitialized
          ? Center(
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  const Text('Niet verbonden met Mini-Me'),
                  ElevatedButton(
                    onPressed: _initializeUdp,
                    child: const Text('Verbind met Mini-Me'),
                  ),
                ],
              ),
            )
          : Column(
              children: [
                Card(
                  margin: const EdgeInsets.all(16),
                  child: Padding(
                    padding: const EdgeInsets.all(16),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.stretch,
                      children: [
                        Center(
                          child: ElevatedButton(
                            onPressed: _isSending ? null : _sendServoReset,
                            child: const Text('Reset Positie'),
                          ),
                        ),
                        if (_isSending) ...[
                          const SizedBox(height: 16),
                          const Center(child: CircularProgressIndicator()),
                        ],
                      ],
                    ),
                  ),
                ),
                Expanded(
                  child: ListView.builder(
                    itemCount: _servos.length,
                    itemBuilder: (context, index) {
                      final servo = _servos[index];
                      return Card(
                        margin: const EdgeInsets.symmetric(
                          horizontal: 16,
                          vertical: 8,
                        ),
                        child: Padding(
                          padding: const EdgeInsets.all(16),
                          child: Column(
                            crossAxisAlignment: CrossAxisAlignment.start,
                            children: [
                              Text(
                                servo['name'].toString(),
                                style: Theme.of(context).textTheme.titleMedium,
                              ),
                              const SizedBox(height: 8),
                              Row(
                                children: [
                                  Expanded(
                                    child: Slider(
                                      value: servo['angle'].toDouble(),
                                      min: 0,
                                      max: 180,
                                      divisions: 180,
                                      label: '${servo['angle']}°',
                                      onChanged: _isSending
                                          ? null
                                          : (value) async {
                                              setState(() {
                                                servo['angle'] = value.round();
                                              });
                                              try {
                                                await _udpService
                                                    .sendServoCommand(
                                                  servo['id'] as int,
                                                  value.round(),
                                                );
                                              } catch (error) {
                                                print(
                                                    'Fout bij het verzenden van opdracht: $error');
                                                if (mounted) {
                                                  ScaffoldMessenger.of(context)
                                                      .showSnackBar(
                                                    SnackBar(
                                                        content: Text(
                                                            'Fout: $error')),
                                                  );
                                                }
                                              }
                                            },
                                    ),
                                  ),
                                  SizedBox(
                                    width: 50,
                                    child: Text(
                                      '${servo['angle']}°',
                                      textAlign: TextAlign.center,
                                    ),
                                  ),
                                ],
                              ),
                            ],
                          ),
                        ),
                      );
                    },
                  ),
                ),
              ],
            ),
    );
  }

  @override
  void dispose() {
    _udpService.dispose();
    super.dispose();
  }
}
