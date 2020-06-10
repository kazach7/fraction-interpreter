#ifndef H_KAZACHTKOM_STATEMENT
#define H_KAZACHTKOM_STATEMENT
namespace kazachTKOM{

class Environment;

class Statement{
public:
    virtual ~Statement() {}
    virtual void execute(Environment&) = 0;
};

}
#endif // H_KAZACHTKOM_STATEMENT
