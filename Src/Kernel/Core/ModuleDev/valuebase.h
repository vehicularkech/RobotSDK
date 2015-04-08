#ifndef VALUEBASE
#define VALUEBASE

#include<Core/ModuleDev/defines.h>

namespace RobotSDK
{

class XMLValueBase
{
public:
    XMLValueBase();
    virtual ~XMLValueBase();
protected:
    QList< std::function< void(XMLDomInterface &, XMLValueBase *) > > _xmlloadfunclist;
public:
    void loadXMLValues(QString configFileName, QString nodeClass, QString nodeName);
};

class XMLParamsBase : public XMLValueBase
{
    friend class Node;
public:
    XMLParamsBase();
    ~XMLParamsBase();
protected:
    QString _nodeclass;
    QString _nodename;
    QString _exname;
public:
    QString getNodeClass();
    QString getNodeName();
    QString getExName();
};

class NodeSwitcher : public QPushButton
{
    Q_OBJECT
    friend class Node;
public:
    static const int SwitchEventType;
    static const int OpenNodeEventType;
    static const int CloseNodeEventType;
protected:
    QObject * _node;
public:
    NodeSwitcher(QWidget * parent=0);
public slots:
    void slotSwitchNode();
};

class WidgetSwitcher : public QPushButton
{
    Q_OBJECT
public:
    WidgetSwitcher(QWidget * parent=0);
protected:
    bool visibleflag;
public slots:
    void slotSwitchWidget();
signals:
    void signalSwitchWidget(bool visiable);
};

class XMLVarsBase : public XMLValueBase
{
    friend class InputPorts;
    friend class Node;
public:
    XMLVarsBase();
    ~XMLVarsBase();
protected:
    QMutex _inputportlock;
    uint _inputportnum;
    QVector< uint > _buffersize;
    QVector< ObtainBehavior > _obtaindatabehavior;
    QVector< uint > _obtaindatasize;
    QVector< bool > _triggerflag;
public:
    void setInputPortBufferSize(uint portID, uint bufferSize);
    void setInputPortBufferSize(QList< uint > bufferSize);
    void setInputPortObtainDataBehavior(uint portID, ObtainBehavior obtainDataBehavior);
    void setInputPortObtainDataBehavior(QList< ObtainBehavior > obtainDataBehavior);
    void setInputPortObtainDataSize(uint portID, uint obtainDataSize);
    void setInputPortObtainDataSize(QList< uint > obtainDataSize);
    void setInputPortTriggerFlag(uint portID, bool triggerFlag);
    void setInputPortTriggerFlag(QList< bool > triggerFlag);
protected:
    QMap< QString, QObject * > _qobjecttriggermap;
    QMap< QString, QObject * > _qwidgettriggermap;
    QMultiMap< QObject *, QString > _defaultconnectionmap;
    QMultiMap< QObject *, QPair< QString, QString > > _userconnectionmap;
    QMultiMap< QPair< QObject *, QObject * > , QPair< QString, QString > > _connectionmap;
    QMap< QString, QWidget * > _qwidgetmap;
    QMap< QString, QLayout * > _qlayoutmap;
public:
    ADD_QWIDGET(QWidget, widget)
    ADD_QWIDGET(NodeSwitcher, nodeSwitcher)
    ADD_QWIDGET(WidgetSwitcher, widgetSwitcher)
    ADD_CONNECTION(widgetSwitcher, signalSwitchWidget, widget, setVisible, bool)
private:
    void moveTriggerToPoolThread(QObject * node, QThread *poolThread);
public:
    QWidget * getWidget() const;
protected:
    QObject * _node;
public:
    const QObject *getNode();
};

class XMLDataBase : public XMLValueBase
{
    friend class OutputPort;
public:
    XMLDataBase();
    ~XMLDataBase();
protected:
    QList< bool > _filterflag;
    uint portid;
public:
    void setOutputPortFilterFlag(QList< bool > filterFlag);
public:
    QTime timestamp;
};

}

#endif // VALUEBASE

