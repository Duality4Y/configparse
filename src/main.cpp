#include <iostream>
#include <vector>
#include <typeinfo>

#define UNUSED(X) ((void)X)

using std::cout;
using std::endl;

std::string config = "configs/test.conf";

class Node
{
public:
    Node(std::string *, std::string *);
    template <typename T> T as();
private:
    std::string *name;
    std::string *value;
    std::vector<Node> subnodes;
    std::vector<Node> nextnodes;
};

Node::Node(std::string *name, std::string *value)
{
    UNUSED(name);
    UNUSED(value);
}

template <typename T>
T Node::as()
{
    cout << "unsupported type: " << typeid(T).name() << " <Exiting>" << endl;
    exit(1);
}

template <>
int Node::as<int>()
{
    cout << "a value of int was requested." << endl;
    return 0x64;
}


class Parser
{
public:
    Parser(std::string);
    void process();
    std::vector<Node> top_nodes;
private:
    std::string configfile;
};

Parser::Parser(std::string config)
{
    this->configfile = config;
    // test some nodes.
    std::string aname = "Hello";
    std::string avalue = "World";
    Node a = Node(&aname, &avalue);
    a.as<int>();
    std::string atest = a.as<std::string>();
}

void Parser::process()
{

}

int main(void)
{
    Parser confparse = Parser(config);
    return 0;
}
