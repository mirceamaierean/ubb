import 'package:flutter/material.dart';

class ErrorScreen extends StatelessWidget {
  final String errorMessage;

  const ErrorScreen({required this.errorMessage, super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Error'),
      ),
      body: Center(
        child: Text(
          errorMessage,
          style: TextStyle(color: Colors.red, fontSize: 18),
          textAlign: TextAlign.center,
        ),
      ),
    );
  }
}
