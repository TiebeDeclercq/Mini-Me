import 'dart:async';
import 'dart:convert';
import 'package:udp/udp.dart';

/// Beheert de UDP-verbinding en het verzenden van berichten
class UdpService {
  UDP? _sender;
  final int port;
  final String address;
  bool _isInitialized = false;

  UdpService({
    required this.port,
    required this.address,
  });

  /// Initialiseert de UDP-verbinding
  Future<void> initializeUDP() async {
    try {
      _sender = await UDP.bind(Endpoint.any(port: Port(0)));
      _isInitialized = true;
      print('UDP succesvol geïnitialiseerd');
    } catch (e) {
      print('Fout bij het initialiseren van UDP: $e');
      _isInitialized = false;
      throw Exception('Kon UDP niet initialiseren: $e');
    }
  }

  /// Algemene methode om berichten te verzenden
  Future<void> sendMessage(Map<String, dynamic> message) async {
    if (!_isInitialized || _sender == null) {
      throw Exception('UDP-zender niet geïnitialiseerd');
    }

    final jsonString = jsonEncode(message);
    print('Bericht verzenden: $jsonString');

    try {
      final result = await _sender?.send(
        jsonString.codeUnits,
        Endpoint.broadcast(port: Port(port)),
      );
      print('Bericht verzonden. Resultaat: $result');
    } catch (e) {
      print('Fout bij het verzenden van bericht: $e');
      throw Exception('Kon bericht niet verzenden: $e');
    }
  }

  /// Verzendt een enkele servo-opdracht
  Future<void> sendServoCommand(int servoId, int angle) async {
    if (!_isInitialized || _sender == null) {
      throw Exception('UDP-zender niet geïnitialiseerd');
    }

    if (angle < 0 || angle > 180) {
      throw Exception('Ongeldige hoek: moet tussen 0 en 180 zijn');
    }

    final message = {'servo': servoId, 'angle': angle};
    await sendMessage(message);
  }

  /// Verzendt meerdere servo-opdrachten
  Future<void> sendMultipleServoCommands(
      List<Map<String, int>> servoCommands) async {
    if (!_isInitialized || _sender == null) {
      throw Exception('UDP-zender niet geïnitialiseerd');
    }

    final message = {'servos': servoCommands};
    await sendMessage(message);
  }

  /// Controleert of de UDP-verbinding is geïnitialiseerd
  bool isInitialized() {
    return _isInitialized;
  }

  /// Sluit de UDP-verbinding en ruimt op
  void dispose() {
    _sender?.close();
    _isInitialized = false;
    print('UDP-service afgesloten');
  }
}
