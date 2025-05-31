import 'package:flutter/material.dart';
import 'package:mini_me/screens/settings.dart';
import 'package:mini_me/screens/about.dart';
import 'package:mini_me/screens/tabs.dart';

class AppDrawer extends StatelessWidget {
  final String currentRoute;

  const AppDrawer({super.key, required this.currentRoute});

  @override
  Widget build(BuildContext context) {
    return Drawer(
      child: LayoutBuilder(
        builder: (context, constraints) {
          return SingleChildScrollView(
            child: ConstrainedBox(
              constraints: BoxConstraints(minHeight: constraints.maxHeight),
              child: IntrinsicHeight(
                child: Column(
                  children: <Widget>[
                    Container(
                      padding: EdgeInsets.only(
                        top: MediaQuery.of(context).padding.top,
                        bottom: 16,
                        left: 16,
                        right: 16,
                      ),
                    ),
                    ListTile(
                      leading: const Icon(Icons.home),
                      title: const Text('Home'),
                      onTap: () {
                        Navigator.of(context).pop();
                        if (currentRoute != '/') {
                          Navigator.of(context).pushAndRemoveUntil(
                            MaterialPageRoute(
                                builder: (context) => const TabsScreen()),
                            (Route<dynamic> route) => false,
                          );
                        }
                      },
                    ),
                    ListTile(
                      leading: const Icon(Icons.settings),
                      title: const Text('Instellingen'),
                      onTap: () {
                        Navigator.pop(context);
                        if (currentRoute != '/settings') {
                          Navigator.push(
                            context,
                            MaterialPageRoute(
                                builder: (context) => const SettingsScreen()),
                          );
                        }
                      },
                    ),
                    ListTile(
                      leading: const Icon(Icons.info),
                      title: const Text('Over'),
                      onTap: () {
                        Navigator.pop(context);
                        if (currentRoute != '/about') {
                          Navigator.push(
                            context,
                            MaterialPageRoute(
                                builder: (context) => const AboutScreen()),
                          );
                        }
                      },
                    ),
                    const Spacer(),
                    Padding(
                      padding: const EdgeInsets.all(16.0),
                      child: Text(
                        '©Dectronics 2025',
                        style: TextStyle(
                          color: Theme.of(context).colorScheme.secondary,
                          fontSize: 12,
                        ),
                      ),
                    ),
                  ],
                ),
              ),
            ),
          );
        },
      ),
    );
  }
}
