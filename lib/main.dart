import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        debugShowCheckedModeBanner: false,
        title: 'Flutter Demo',
        theme: ThemeData(
          primarySwatch: Colors.purple,
          visualDensity: VisualDensity.adaptivePlatformDensity,
        ),
        home: HomePage());
  }
}

class HomePage extends StatefulWidget {
  @override
  _HomePageState createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  final DBref = FirebaseDatabase.instance.reference();
  int led = 0;
  bool isLoading = false;

  getled() async {
    await DBref.child('led').once().then((DataSnapshot snapshot) {
      led = snapshot.value;
      print(led);
    });

    setState(() {
      isLoading = false;
    });
  }

  @override
  void initState() {
    isLoading = true;
    getled();
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(
          'HomeTess',
          style:
              GoogleFonts.montserrat(fontSize: 25, fontStyle: FontStyle.italic),
        ),
      ),
      body: Center(
        child: isLoading
            ? CircularProgressIndicator()
            : RaisedButton(
              
                child: Text(
                  led == 0 ? 'Ligar' : 'Desligar',
                  
                  style: GoogleFonts.nunito(
                      fontSize: 20, fontWeight: FontWeight.w300),
                ),
                onPressed: () {
                  buttonPressed();
                },
              ),
      ),
    );
  }

  void buttonPressed() {
    led == 0
        ? DBref.child('led').set(1)
        : DBref.child('led').set(0);
    if (led == 0) {
      setState(() {
        led = 1;
      });
    } else {
      setState(() {
        led = 0;
      });
    }
  }
}