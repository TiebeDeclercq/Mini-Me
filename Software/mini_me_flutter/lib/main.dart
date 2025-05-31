import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:mini_me/managers/data_manager.dart';
import 'package:mini_me/screens/tabs.dart';
import 'package:mini_me/services/udp_service.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  // Initialiseer DataManager
  await DataManager.initialize();

  // Initialiseer UDP Service
  final udpService = UdpService(
    port: 5005,
    address: '10.198.112.11',
  );
  await udpService.initializeUDP();

  // Laad de thema voorkeur
  final isDarkMode = await DataManager.getIsDarkMode();

  runApp(MyApp(isDarkMode: isDarkMode));
}

class MyApp extends StatefulWidget {
  final bool isDarkMode;

  const MyApp({super.key, required this.isDarkMode});

  @override
  State<MyApp> createState() => _MyAppState();

  static _MyAppState of(BuildContext context) =>
      context.findAncestorStateOfType<_MyAppState>()!;
}

class _MyAppState extends State<MyApp> {
  late bool _isDarkMode;

  @override
  void initState() {
    super.initState();
    _isDarkMode = widget.isDarkMode;
  }

  /// Wisselt tussen licht en donker thema
  void toggleTheme() {
    setState(() {
      _isDarkMode = !_isDarkMode;
    });
    DataManager.setIsDarkMode(_isDarkMode);
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Mini-Me',
      theme: _isDarkMode ? _darkTheme : _lightTheme,
      home: const TabsScreen(),
    );
  }
}

/// Licht thema configuratie
final _lightTheme = ThemeData(
  useMaterial3: true,
  colorScheme: ColorScheme.fromSeed(
    brightness: Brightness.light,
    seedColor: Colors.red,
  ),
  textTheme: GoogleFonts.latoTextTheme(),
);

/// Donker thema configuratie
final _darkTheme = ThemeData(
  useMaterial3: true,
  colorScheme: ColorScheme.fromSeed(
    brightness: Brightness.dark,
    seedColor: Colors.red,
  ),
  textTheme: GoogleFonts.latoTextTheme(),
);
