import 'package:flutter/material.dart';
import 'package:mini_me/widgets/app_drawer.dart';
import 'package:mini_me/widgets/styled_text.dart';

class AboutScreen extends StatelessWidget {
  const AboutScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Over'),
      ),
      drawer: const AppDrawer(currentRoute: '/about'),
      body: const Column(
        children: [
          const Padding(
            padding: EdgeInsets.all(16.0),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.center,
              children: [
                StyledText(
                  text: 'Mini-me',
                  variant: TextStyleVariant.titleLarge,
                ),
                SizedBox(height: 16),
                StyledText(
                  text: 'Versie: 0.1.0',
                ),
                SizedBox(height: 16),
                StyledText(
                  text:
                      'Bestuur je eigen Mini-Me met deze eenvoudig te gebruiken app!',
                ),
                SizedBox(height: 24),
                StyledText(
                  text: 'Ontwikkeld door: Tiebe Declercq',
                ),
              ],
            ),
          ),
          Spacer(), // This will push the text to the bottom
          Padding(
            padding: EdgeInsets.all(16.0),
            child: StyledText(
              text: '©Dectronics 2025',
            ),
          ),
        ],
      ),
    );
  }
}
