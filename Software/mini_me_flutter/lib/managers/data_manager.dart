import 'package:shared_preferences/shared_preferences.dart';

/// Beheert gegevenspersistentie en ophaling
class DataManager {
  // Sleutels voor SharedPreferences opslag
  static const String _isInitializedKey = 'isInitialized';
  static const String _isDarkModeKey = 'isDarkMode';
  static const String _isDebugModeKey = 'isDebugMode';

  // SharedPreferences instantie
  static SharedPreferences? _prefs;

  /// Initialiseert de DataManager en laadt indien nodig initiële gegevens.
  static Future<void> initialize() async {
    // Verkrijg SharedPreferences instantie
    _prefs = await SharedPreferences.getInstance();

    // Controleer of de app eerder is geïnitialiseerd
    bool isInitialized = _prefs!.getBool(_isInitializedKey) ?? false;
    if (!isInitialized) {
      // Laad dummy gegevens bij de eerste keer opstarten

      await _prefs!.setBool(_isInitializedKey, true);
    }
  }

  /// Reset de app naar de initiële staat en wist alle gegevens.
  static Future<void> resetToInitialState() async {
    await _prefs!.remove(_isInitializedKey);
    await initialize();
  }

  /// Haalt de dark mode instelling op.
  static Future<bool> getIsDarkMode() async {
    return _prefs!.getBool(_isDarkModeKey) ?? false;
  }

  /// Stelt de dark mode instelling in.
  static Future<void> setIsDarkMode(bool value) async {
    await _prefs!.setBool(_isDarkModeKey, value);
  }

  /// Haalt de debug mode instelling op.
  static Future<bool> getIsDebugMode() async {
    return _prefs!.getBool(_isDebugModeKey) ?? false;
  }

  /// Stelt de debug mode instelling in.
  static Future<void> setIsDebugMode(bool value) async {
    await _prefs!.setBool(_isDebugModeKey, value);
  }
}
