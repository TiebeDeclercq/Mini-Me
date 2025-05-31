import 'package:flutter/material.dart';

class ConnectScreen extends StatelessWidget {
  final VoidCallback onConnect;
  final VoidCallback onSkip;

  const ConnectScreen({
    super.key,
    required this.onConnect,
    required this.onSkip,
  });

  @override
  Widget build(BuildContext context) {
    final colorScheme = Theme.of(context).colorScheme;

    return Scaffold(
      backgroundColor: Theme.of(context).colorScheme.surface,
      appBar: AppBar(
        title: const Text('Verbind met Mini-Me'),
        leading: IconButton(
          icon: const Icon(Icons.menu),
          onPressed: () => Scaffold.of(context).openDrawer(),
        ),
        actions: [
          ElevatedButton.icon(
            onPressed: onSkip,
            icon: const Icon(Icons.skip_next),
            label: const Text('Overslaan'),
            style: ElevatedButton.styleFrom(
              foregroundColor: colorScheme.onPrimary,
              backgroundColor: colorScheme.primary,
            ),
          ),
        ],
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            const Icon(Icons.warning, size: 48),
            const SizedBox(height: 16),
            const Text(
              'Niet verbonden met Mini-Me',
              style: TextStyle(fontSize: 20),
            ),
            const SizedBox(height: 24),
            ElevatedButton.icon(
              onPressed: onConnect,
              icon: const Icon(Icons.wifi),
              label: const Text('Verbind met Mini-Me'),
              style: ElevatedButton.styleFrom(
                padding: const EdgeInsets.symmetric(
                  horizontal: 32,
                  vertical: 16,
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
