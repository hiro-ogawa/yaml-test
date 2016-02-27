/**
 * Get yaml informations by yaml-cpp.
 */
#include <string>
#include <iostream>
#include <yaml-cpp/yaml.h>

using namespace std;


void CheckType(YAML::Node node);

void ParseMap(YAML::Node node)
{
  cout << "ParseMap" << endl;

  for(YAML::const_iterator it = node.begin(); it != node.end(); it++)
  {
    YAML::Node key = it->first;
    YAML::Node value = it->second;
    CheckType(key);
    CheckType(value);
  }
}

void ParseSequence(YAML::Node node)
{
  cout << "ParseSequence" << endl;

  for(YAML::const_iterator it = node.begin(); it != node.end(); it++)
  {
    CheckType(*it);
  }
}

void CheckType(YAML::Node node)
{
  cout << "CheckType: ";
  switch(node.Type())
  {
  case YAML::NodeType::Null:
    cout << "Null";
    break;
  case YAML::NodeType::Scalar:
    cout << "Scalar: " << node.as<string>();
    break;
  case YAML::NodeType::Sequence:
    cout << "Sequence";
    break;
  case YAML::NodeType::Map:
    cout << "Map";
    break;
  case YAML::NodeType::Undefined:
    cout << "Undefined";
    break;
  default:
    break;
  }
  cout << endl;

  if(node.IsMap()){
    ParseMap(node);
  }
  else if(node.IsSequence()){
    ParseSequence(node);
  }
}

void printScalar(YAML::Node node, int depth=0)
{
  // if(node.Tag() == "tag:yaml.org,2002:binary")
  //   cout << node.Tag() << endl;
  for(int i=0;i<depth;i++)
    cout << "  ";
  if(node.Tag() == "tag:yaml.org,2002:binary"){
    // vector<unsigned char> bin;
    // bin = YAML::DecodeBase64(node.as<string>());
    // bin = node.as< vector<unsigned char> >();
    // cout << "BIN: ";
    // for(int i=0;i<bin.size();i++)
    //   cout << bin[i] << " ";
    // cout << endl;
    cout << node.as<string>() << endl;
  }
  else{
    cout << node.as<string>() << endl;
  }
}

void printNode(YAML::Node node, int depth=0);
void printMap(YAML::Node node, int depth=0)
{
  for(YAML::const_iterator it = node.begin(); it != node.end(); it++)
  {
    printNode(it->first, depth);
    printNode(it->second, depth+1);
  }
}

void printSeq(YAML::Node node, int depth=0)
{
  for(YAML::const_iterator it = node.begin(); it != node.end(); it++)
  {
    printNode(*it, depth+1);
  }
}

void printNode(YAML::Node node, int depth)
{
  switch(node.Type())
  {
  case YAML::NodeType::Scalar:
    printScalar(node, depth);
    break;
  case YAML::NodeType::Sequence:
    printSeq(node, depth);
    break;
  case YAML::NodeType::Map:
    printMap(node, depth);
    break;
  case YAML::NodeType::Null:
  case YAML::NodeType::Undefined:
  default:
    break;
  }
}

int main(int argc, char* argv[]){
  try{
    YAML::Node config = YAML::LoadFile("config.yml");
    // string hostname = config["db"]["hostname"].as<string>();
    // string database = config["db"]["database"].as<string>();
    // string username = config["db"]["username"].as<string>();
    // string password = config["db"]["password"].as<string>();
    // cout << "* DB Setting:\n"
    //      << "  - HOSTNAME: " << hostname << "\n"
    //      << "  - DATABASE: " << database << "\n"
    //      << "  - USERNAME: " << username << "\n"
    //      << "  - PASSWORD: " << password << endl;

    // CheckType(config);
    printNode(config);
    // CheckType(config["abcd"]);
    // CheckType(config.begin()->first);
    // CheckType(config.begin()->second);
    // CheckType(config[0]);
    // CheckType(config["num"]);
    // CheckType(config["num2"]);
    // CheckType(config["date"]);
    // CheckType(config["db"]);
    // CheckType(config["db"][0]);
    // CheckType(config["db"].begin()->first);
    // CheckType(config["db"].begin()->second);
    CheckType(config["test"]);
    cout << endl;

    YAML::Node n = YAML::Load("[1 2 3]");
    printNode(n);

    YAML::Node lineup = YAML::Load("{1B: Prince Fielder, 2B: Rickie Weeks, LF: Ryan Braun}");
    printNode(lineup);

    for(YAML::const_iterator it=lineup.begin();it!=lineup.end();++it) {
      std::cout << "Playing at " << it->first.as<std::string>() << " is " << it->second.as<std::string>() << "\n";
    }
    // for(int i=0;i<lineup.size();i++) {
    //   std::cout << "Playing at " << lineup.first.as<std::string>() << " is " << lineup.second.as<std::string>() << "\n";
    // }

    lineup["RF"] = "Corey Hart";
    lineup["C"] = "Jonathan Lucroy";
    assert(lineup.size() == 5);

    YAML::Emitter emitter;
    emitter << YAML::Binary((unsigned char *)"Hello, World!", 14);
    cout << emitter.c_str() << endl;
  }
  catch(YAML::Exception& e) {
      cerr << e.what() << endl;
  }
  return 0;
}
