#ifndef WITNESS_H
#define WITNESS_H
#include<QString>
class Witness
{
public:
    Witness() {};
    static bool enable_Witness;
    static const QString strLocation;
    static const QString strEvent;
    static const QString strEvt_FunctionFailed;
    static const QString strVariable;
    static const QString strVar_Input;
    static const QString strVar_Output;
};

#endif // WITNESS_H
