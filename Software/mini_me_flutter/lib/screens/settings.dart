import 'package:flutter/material.dart';
import 'package:mini_me/main.dart';
import 'package:mini_me/managers/data_manager.dart';
import 'package:mini_me/widgets/app_drawer.dart';
import 'package:mini_me/widgets/styled_text.dart';

class SettingsScreen extends StatefulWidget {
  const SettingsScreen({super.key});

  @override
  _SettingsScreenState createState() => _SettingsScreenState();
}

class _SettingsScreenState extends State<SettingsScreen> {
  late bool _isDarkMode = false;
  bool _debugMode = false;
  String _lblTheme = "Light Mode";

  @override
  void initState() {
    super.initState();
    _loadSettings();
  }

  Future<void> _loadSettings() async {
    final isDarkMode = await DataManager.getIsDarkMode();
    final isDebugMode = await DataManager.getIsDebugMode();
    setState(() {
      _isDarkMode = !isDarkMode;
      _debugMode = isDebugMode;
    });
  }

  void _toggleMode(bool value) async {
    await DataManager.setIsDarkMode(value);
    setState(() {
      _isDarkMode = value;
      _lblTheme = _isDarkMode ? "Light Mode" : "Dark Mode";
    });
    MyApp.of(context).toggleTheme();
  }

  void _toggleDebugMode(bool value) async {
    await DataManager.setIsDebugMode(value);
    setState(() {
      _debugMode = value;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Instellingen'),
      ),
      drawer: const AppDrawer(currentRoute: '/settings'),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            _buildSwitchRow(_lblTheme, _isDarkMode, _toggleMode),
            _buildSwitchRow('Debug Mode', _debugMode, _toggleDebugMode),
          ],
        ),
      ),
    );
  }

  Widget _buildSwitchRow(String label, bool value, Function(bool) onChanged) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 4.0, horizontal: 16.0),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          StyledText(text: label),
          const SizedBox(width: 16),
          Switch(
            value: value,
            onChanged: onChanged,
          ),
        ],
      ),
    );
  }
}
