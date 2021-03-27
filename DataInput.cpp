/*
 * DataInput.cpp
 * Friday, March 26, 2021
 * Calvin Hackathon, group HJ
 *      Authors: Jacob Westra
 *               Haim Hong
 * Program description:
 * Reads values from data.txt
 * Auto-generates HTML pages based on the data
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // declare local vars
    string name = "";
    string agency = "";
    string yearLaunched = "";
    string currentlyActive = "";
    string whereabouts = "";
    string status = "";
    string wikipediaLink = "";
    string previousName = "";

	    string filename = "data.txt"; // primary input file
		string current;
        // counting variables
        int n = 0;
		int i = 0;
		int local = 0; // distinguishes between input parameters, can be 0-8
		ifstream ifs(filename, ifstream::in);
		  char c = ifs.get();
          // loops through the input file char-by-char, and then assembles the characters into strings
          ofstream AllArticles("All-articles.html"); // each article added to All-articles.html
                // this section adds the header to the All-articles.html file
                AllArticles << "" << '\n';
                AllArticles << "<!DOCTYPE html><title>All articles - CaMEO Index</title><html><head><style>" << '\n';
                AllArticles << "div { max-width: 50%;}" << '\n';
                AllArticles << "</style></head><body>" << '\n';
                AllArticles << "<b><titletext style=\"font-size:20px;\">All articles</titletext></b>" << '\n';
                AllArticles << "<hr><tt><a href=\"https://jw021.github.io/CaMEO/index.html\" target=\"_self\">CaMEO</a> index page</tt><br><tt></p>" << '\n';
		  while (ifs.good()) {
		    current+=c; // add current char to string
            if(local == 8){ // reset after all 7 parameters are filled (name-link)
                local = 0;
            }
		    if(c == '\n'){ // if current char is newline
                string current2 = current.substr(0,current.length()-1); // cuts off the "/n" character from the end of current
                switch (local){
                    case 0: // Mission name
                        name = current2;
                        break;
                    case 1: // Space agency
                        agency = current2;
                        break;
                    case 2: // Year launched
                        yearLaunched = current2;
                        break;
                    case 3: // Currently active
                        currentlyActive = current2;
                        break;
                    case 4: // Whereabouts
                        whereabouts = current2;
                        break;
                    case 5: // Status
                        status = current2;
                        break;
                    case 6: // Wikipedia link
                        wikipediaLink = current2;
                        break;
                    case 7: // End
                         //generates the webpage. Yeah the code is ugly
                         //start make webpage
                                ofstream MyFile(name + ".html");
                                MyFile << " <!DOCTYPE html><title> " + name + " (" + agency + + ") - CaMEO Index</title><html><head><style> " << '\n';
                                MyFile << " div { max-width: 50%;} .Activedot { height: 7px; width: 7px; background-color: #5FB92B; border-radius: 50%; display: inline-block; } .Inactivedot { height: 7px; width: 7px; background-color: #BD2C2C; border-radius: 50%; display: inline-block; } " << '\n';
                                MyFile << " </style></head><body>" << '\n';
                                MyFile << " <b><titletext style=\"font-size:20px;\">" + name + "</titletext></b> " << '\n';
                                MyFile << " <hr><tt><a href=\"https://jw021.github.io/CaMEO/index.html\" target=\"_self\">CaMEO</a> index page</tt><br><tt><p style=\"border:1px; border-style:solid; border-color:#000000; padding: 0.5em; max-width: 50%;\"> <b>Mission information</b> " << '\n';
                                MyFile << " <br>Name: " + name << '\n';
                                MyFile << " <br>Agency of origin: " + agency << '\n';
                                MyFile << " <br>Year Launched: " + yearLaunched  << '\n';
                                MyFile << " </p> <p style=\"border:1px; border-style:solid; border-color:#000000; padding: 0.5em; max-width: 50%;\"><b>Current status</b> " << '\n';
                                MyFile << " <br>Current activity: <span class=\"" + currentlyActive + "dot\"></span> " + currentlyActive << '\n';
                                MyFile << " <br>Current whereabouts: " + whereabouts << '\n';
                                MyFile << " <br>Status: " + status << '\n';
                                MyFile << " </p><tt><a href=\"" + wikipediaLink +  "\" target=\"_self\">Wikipedia article</a></tt> " << '\n';
                                MyFile << " <br> <br>See also: " << '\n';
                                MyFile << " <br><a href=\"" + previousName + ".html\" target=\"_self\">" + previousName + " Article</a> " << '\n';
                                MyFile << " </tt><br><tt> <div class=\"btext\"><p>Page rendered <span id=\"datetime\"></span>. Auto-generated by a <a href=\"DataInput.cpp\" target=\"_self\">C++ program</a>. </p></div></tt><script> var dt = new Date(); document.getElementById(\"datetime\").innerHTML = dt.toLocaleString(); </script> </body> </html>  " << '\n';
                                MyFile.close();
                         // end make webpage
                         // add article to All-articles list
                         AllArticles << "<tt>" + to_string(n+1) + ": <a href=\"" + name + ".html\" target=\"_self\">" + name + "</a></tt><br>" << '\n';
                         previousName = name;
                         n++;
                         cout << n << ": " << name << " HTML generated." << endl; // for debug purposes

                        break;
                }
                local++;
		    	i++;
		    	current = ""; // reset current
		    }
		    c = ifs.get();
		  }
          // after data-retrieving is done, wrap-up the All-articles.html file
          AllArticles << "<br>Auto-generated by a C++ program</tt></body> </html>" << '\n';
          AllArticles.close();
}
