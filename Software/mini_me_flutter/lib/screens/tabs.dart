import 'package:flutter/material.dart';
import 'package:mini_me/screens/interact.dart';
import 'package:mini_me/mlkit/pose_detector_view.dart';
import 'package:mini_me/widgets/app_drawer.dart';

class TabsScreen extends StatefulWidget {
  const TabsScreen({super.key});

  @override
  State<TabsScreen> createState() => _TabsScreenState();
}

class _TabsScreenState extends State<TabsScreen> {
  int _selectedPageIndex = 0;

  @override
  void initState() {
    super.initState();
  }

  /// Bouwt het scherm op basis van de geselecteerde pagina
  Widget _buildScreen() {
    switch (_selectedPageIndex) {
      case 0:
        return const InteractScreen();
      case 1:
        return PoseDetectorView();
      default:
        return const InteractScreen();
    }
  }

  /// Selecteert een pagina in de navigatiebalk
  void _selectPage(int index) {
    setState(() {
      _selectedPageIndex = index;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      drawer: const AppDrawer(currentRoute: '/'),
      body: _buildScreen(),
      bottomNavigationBar: BottomNavigationBar(
        currentIndex: _selectedPageIndex,
        onTap: _selectPage,
        items: const [
          BottomNavigationBarItem(
            icon: Icon(Icons.control_camera),
            label: 'Control',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.camera),
            label: 'Pose Detection',
          ),
        ],
      ),
    );
  }

  @override
  void dispose() {
    super.dispose();
  }
}
