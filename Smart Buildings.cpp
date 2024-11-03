#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <windows.h>
using namespace std;

class Smart_Buildings
{
  //default class private
  string name, address, floor, power;
public:
  //name
  void set_name(string& get_name) {name = get_name;}
  //address
  void set_address(string& get_address) {address = get_address;}
  //floor
  void set_floor(string& get_floor) {floor = get_floor;}
  /*
    power
    features 
    [1]edit usage power
  */
  void set_power(string& get_power) {power = get_power, power.push_back('%');}
  
  //get function
  string get_name() { return name; }
  string get_address() { return address; }
  string get_floor() { return floor; }
  string get_power() { return power; }
};

//get length
int len(string get_len) { return get_len.size(); }
//check string
bool check(string get_str,string var = "default")
{
  //power and floor
  if (var == "default")
  {
    for (char& z : get_str)
      if (isalpha(z) || ispunct(z) || isspace(z)) return true;
  }
  //name
  else if (var == "name")
  {
    if (ispunct(get_str.at(0)) && get_str.at(0) != '_') return true;
    if (isspace(get_str.at(0)) || isdigit(get_str.at(0))) return true;
    for (int i = 1; i < get_str.size(); ++i)
      if (ispunct(get_str.at(i)) || isspace(get_str.at(i)) || isdigit(get_str.at(i))) return true;
  }
  //address
  else if(var == "address")
  {
    if(ispunct(get_str.at(0)) || isspace(get_str.at(0))) return true;
    for (int i = 1; i < get_str.size(); ++i)
      if(ispunct(get_str.at(i))) return true;
  }
  return false;
}
//check name
void check_name(string& get_name)
{
  cout << "Enter build name: ";
  getline(cin, get_name);
  string str = "name";
  while(len(get_name) < 4 || len(get_name) > 15 || check(get_name, str))
  {
    cout << "Error!, contains is (4 letters >= build name <= 15 letters)\n";
    cout << "Please re-enter the a valid name: ";
    getline(cin, get_name);
  }
}
//check address
void check_address(string& get_address)
{
  cout << "Enter build address: ";
  getline(cin, get_address);
  string str = "address";
  while(len(get_address) < 4 || len(get_address) > 20 || check(get_address, str))
  {
    cerr << "Error!, Contains is (4 letters >= Build Address <= 20 letters)\n";
    cout << "Please re-enter the a valid address: ";
    getline(cin, get_address);
  }
}
//check floor
void check_floor(string& get_floor)
{
  cout << "Enter building floor number: ";
  getline(cin, get_floor);
  int floor;
  if (!check(get_floor)) floor = stoi(get_floor);
  while(len(get_floor) < 0 || len(get_floor) > 2 || check(get_floor) || floor < 0 || floor > 20)
  {
    cerr << "Error!, contains is (0 <= building floor <= 20)\n";
    cout << "Please re-enter the a valid floor: ";
    getline(cin, get_floor);
    if (!check(get_floor)) floor = stoi(get_floor);
  }
}
//check power
void check_power(string& get_power)
{
  cout << "Enter building power usage: ";
  getline(cin, get_power);
  int pow;
  if (!check(get_power)) pow = stoi(get_power);
  while(len(get_power) <= 0 || len(get_power) > 3 || pow > 100)
  {
    cerr << "Error!, contains is (0 <= power <= 100)\n";
    cout << "Please re-enter the a valid power: ";
    getline(cin, get_power);
    if (!check(get_power)) pow = stoi(get_power);
  }
}

//design 1
void cmd()
{
  cout << "\n[1] Add Smart Build\n";
  cout << "[2] Show Smart Buildings\n";
  cout << "[3] Exit";
  cout << endl;
}

//option 1
void option_one(Smart_Buildings& set_build, vector<Smart_Buildings>& builds)
{
  string name, address, floor, power;
  cout << endl;
  check_name(name);
  set_build.set_name(name);
  check_address(address);
  set_build.set_address(address);
  check_floor(floor);
  set_build.set_floor(floor);
  check_power(power);
  set_build.set_power(power);
  //create file for set buildings
  ofstream outfile("Smart_Builds.txt", ios::app);
  outfile << set_build.get_name() << ',' << set_build.get_address() << ',' << set_build.get_floor() << ',' << set_build.get_power() << "\n";
  builds.push_back(set_build);
  cout << "\nsuccessful added." << endl;
}

//option 2
void option_two(vector<Smart_Buildings>& set_builds)
{
  int i = 0;
  for (Smart_Buildings& build : set_builds)
  {
    cout << "\nBuild Number [" << ++i << "]";
    cout << "\nName: " << build.get_name();
    cout << "\nAddress: " << build.get_address();
    cout << "\nFloor: " << build.get_floor();
    cout << "\nPower: " << build.get_power();
    cout << endl;
  }
}

//design 2
void cmd2()
{
  cout << "\n[1] Edit Build Power Usage";
  cout << "\n[2] Soon";
  cout << "\n[3] Home";
  cout << endl;
}

//option 2 in option 1
void option_one_two(vector<Smart_Buildings>& builds)
{
  int select;
  cout << "\nEnter building number: ";
  cin >> select;
  cin.ignore();
  string power;
  check_power(power);
  builds.at(select - 1).set_power(power);
  cout << "Successful edit.\n";
  ofstream outfile("Smart_Builds.txt");
  for(Smart_Buildings& build : builds)
    outfile << build.get_name() << ',' << build.get_address() << ',' << build.get_floor() << ',' << build.get_power() << "\n";
}

int main()
{
  Smart_Buildings build;
  vector<Smart_Buildings> builds;
  //get buildings from file
  ifstream infile("Smart_Builds.txt");
  string word;
  while(getline(infile, word))
  {
    string name, address, floor, power;
    name = word.substr(0, word.find(','));
    word.erase(0, word.find(',') + 1);
    address = word.substr(0, word.find(','));
    word.erase(0, word.find(',') + 1);
    floor = word.substr(0, word.find(','));
    word.erase(0, word.find(',') + 1);
    power = word;
    power.pop_back();
    word.clear();
    build.set_name(name);
    build.set_address(address);
    build.set_floor(floor);
    build.set_power(power);
    builds.push_back(build);
  }
  for (int i = 0; i <= 100; ++i) 
  {
    cout << "\rLoading " << i;
    Sleep(50);
  }
start:
  cmd();
  string sel;
  getline(cin, sel);
  while(sel.size() > 1 || !(sel.at(0) > '0' && sel.at(0) < '4'))
  {
    cerr << "Error, Please enter a valid option: ";
    getline(cin, sel);
  }
  switch(sel.at(0))
  {
    case '1':
      option_one(build, builds);
      goto start;
    case '2':
    op12:
      option_two(builds);
      cmd2();
      getline(cin, sel);
      while(sel.size() > 1 || !(sel.at(0) > '0' && sel.at(0) < '4'))
      {
        cerr << "Error, Please enter a valid option: ";
        getline(cin, sel);
      }
      if (sel.at(0) == '1') { option_one_two(builds); goto op12; }
      else goto start;
    case '3':
      break;
  }
  return 0;
}