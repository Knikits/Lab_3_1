#ifndef IOCCONTAINER_H
#define IOCCONTAINER_H

#include <iostream>
#include <functional>
#include <cstdlib>
#include <memory>
#include <map>

using namespace std;

/*
Получение кода типа;

Прежде чем мы сможем безопасно сохранить способ получения класса,
подписывающегося на определенный интерфейс, мы должны выделить для этого код типа.

В предложенной реализации  реализации контейнера IOC  есть статическая целочисленная переменная,
которая определяет идентификатор следующего типа, который будет выделен,
и экземпляр статической локальной переменной для каждого типа,
к которому можно обратиться, вызвав метод GetTypeID.
*/

/*Статические функции нужны, чтобы работать со статическими полями!
Статические переменные - это переменные, которые не исчезают после завершения работы функции!
*/

// Цель IOC контейнера состоит в том, чтобы архитектура была независима от создания объекта и управления памятью.

class IOCContainer
{
    static int s_typeId; // статическая целочисленная переменная, которая показывает ID типа
public:
    template<typename T>
    static int GetTypeID()
    {
        static int typeId = s_typeId++;
        return typeId; // возвращение ID типа
    }

    /*
     Получение экземпляров объекта;

     Теперь, когда  есть идентификатор типа, мы должны иметь возможность хранить какой-то фабричный объект,
     чтобы показать тот факт, что мы не знаем, как создать объект.(так как мы не знаем как создать объект)

     Хранить все фабрики в одной коллекции, для этого выбираем абстрактный базовый класс,
     из которого будут производиться фабрики, и реализацию, которая захватывает функтор для последующего вызова.
     Можно использовать std :: map для хранения фабрик,та же можно рассмотреть  другие варианты для эффективности.

    */

    //объявление класса внутри другого класса говорит о том, что создаётся пользовательский тип данных.
    // Пользоваться им можно только внутри этого класса!
    // мы можем создавать указатели из вне, но тогда нужно будет писать такой IOC контейнер
    // интерфейс для фабрики
    class FactoryBase //внутри класса есть этот класс, который является так сказать интерфейсом
    {
    public:
        virtual ~FactoryBase() {} // виртуальный деструктор
    };
    // нужен для организации наследования с дальнейшим добавлением дополнительных свойств

    //todo: consider sorted vector

    // структура карты, что-то наподобии хэш-функции
    // это такая динамическая структура, которая позволяет хранить данные (фабрики) в виде ключ-значения
    // по ключу мы можем быстро добираться до нужных данных
    // первый ключ int, далее умный указатель shared_ptr (разделяемый). Некоторое подмножество объектов имеет право указывать на один и тот же объект в памяти

    map<int, shared_ptr<FactoryBase>> factories; // ключ - ID типа, указатель на объект зависит от базового класса

    template<typename T> // конкретная фабрика (шаблон)
    class CFactory : public FactoryBase
    {
        // специальный класс, который позволяет создавать указатель на функцию, либо определять лямбда функцию
        // нужен для инициализаци
        // std::function
        std::function<std::shared_ptr<T>()> functor;
    public:
        ~CFactory() {} // деструктор
        // конструтор, приходит указатель на функцию, будем инициализировать путём присвоения
        CFactory(std::function<std::shared_ptr<T>()> functor):functor(functor) {}
        std::shared_ptr<T> GetObject()
        {
            return functor(); // возвращаем умный указатель (объект)
        }

    };

    template<typename T>
    // происходит создание реального объекта фабрики
    std::shared_ptr<T> GetObject() // метод GetObject() уже именно для класса IOCContainer
    {
        //для каждого созданного объекта мы формируем идендификационный номер
        auto typeId = GetTypeID<T>(); // получаем ID этой фабрики
        auto factoryBase = factories[typeId]; // относительно ID обращаемся к структуре, где сохраняется объект по этому ключу
        //static_pointer_cast - преобразование типов данных
        auto factory = std::static_pointer_cast<CFactory<T>>(factoryBase); // преобразуем в фабрику конкреткную
        return factory->GetObject(); // возвращаем объект, который берем из functor
    }

    /*
    Регистрация экземпляров
    */

    //Базовая реализация - регистрация функтора
    //
    // Когда работаем с IOC контейнером, мы можем абсолютно любые классы, созданные в системе, регистрировать.
    // Конечно же тут есть определённые правила, здесь используется интерфейс, потом базовый класс..
    // Классы, которые мы создали в системе для дальнейшего взаимодействия, мы должны зарегистрировать
    // Здесь используется лямбда-функция, также используется объект factories и т.д.
    // рекурсивно вызывется GetObject, из-за этого ошибка -> нарушение прав доступа при чтении
    // попытка читать ту область памяти, которая еще не инициализирована
    // по идеи эта функция должна была уже вернуть объект, но она снова вызывает GetObject<TS>
    template<typename TInterface, typename ...TS>
    void RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)> functor)
    {
        factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>([=] {return functor(GetObject<TS>()...); });
    }

    //Регистрация экземпляра объекта
    // создание нового объекта из фабрики
    template<typename TInterface>
    void RegisterInstance(std::shared_ptr<TInterface> t)
    {
        // берем ID интерфейса у фабрики и возвращаем объект этого типа
        factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>([=] {return t; });
    }

    //Работаем с указателем на функцию
    // создает указатель на функцию, используется для создания фабрики
    template<typename TInterface, typename ...TS>
    void RegisterFunctor(std::shared_ptr<TInterface>(*functor)(std::shared_ptr<TS> ...ts))
    {
        // вызываем RegisterFunctor, по сути даем объект TInterface
        RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)>(functor));
    }

    //Фабрика, которая будет вызывать необходимый конструктор для каждого экземпляра
    // нужно для создания нового объекта, который фабрика производит
    // так как мы не знаем заранее какой будет конструктор, сколько будет аргументов, мы реализуем шаблон, который зависит от множества аргументов!!!
    template<typename TInterface, typename TConcrete, typename ...TArguments>
    void RegisterFactory()
    {
        // вызываем RegisterFunctor, по сути даем объект TConcrete
        RegisterFunctor(
            std::function<std::shared_ptr<TInterface>(std::shared_ptr<TArguments> ...ts)>(
                [](std::shared_ptr<TArguments>...arguments) -> std::shared_ptr<TInterface>
        {
            return std::make_shared<TConcrete>(std::forward<std::shared_ptr<TArguments>>(arguments)...);
        }));

    }

    //Фабрика, которая будет возвращать один экземпляр  объекта  для каждого вызова
     // интерфейсная функция, вызывает базовую функцию RegisterInstance и создает экземпляр, который производит фабрика
    template<typename TInterface, typename TConcrete, typename ...TArguments>
    void RegisterInstance()
    {
        RegisterInstance<TInterface>(std::make_shared<TConcrete>(GetObject<TArguments>()...));
    }
};

IOCContainer gContainer;

//Иницализация не нулевым значением

int IOCContainer::s_typeId = 121;

/*

//Здесь, примеры различных интерфесов, классов
///////////////////////////////////////////////////////////////////////////
 // интерфейс какого-то объекта
class ISomeObjX
{
public:
    virtual ~ISomeObjX() { }
    virtual void TestMethodX() = 0;
};

///////////////////////////////////////////////////////////////////////////
// ObjX - наследник какого-то объекта
class ObjX : public ISomeObjX
{
public:
    ObjX() {}
    void TestMethodX()
    {
        std::cout << "This is ObjX" << std::endl;
    }

};

///////////////////////////////////////////////////////////////////////////
// интерфейс вещи
class IAmAThing
{
public:
    virtual ~IAmAThing() { }
    virtual void TestThis() = 0;
};


///////////////////////////////////////////////////////////////////////////
// интерфейс другой вещи
class IAmTheOtherThing
{
public:
    virtual ~IAmTheOtherThing() { }
    virtual void TheOtherTest() = 0;
};


///////////////////////////////////////////////////////////////////////////
// наследник iAmThing
class TheThing : public IAmAThing
{
public:
    TheThing() {}
    void TestThis()
    {
        std::cout << "A Thing" << std::endl;
    }
};

///////////////////////////////////////////////////////////////////////////
// реализация другой вещи
class TheOtherThing : public IAmTheOtherThing
{
    std::shared_ptr<IAmAThing> m_thing;
public:
    TheOtherThing(std::shared_ptr<IAmAThing> thing) :m_thing(thing) {}
    void TheOtherTest()
    {
        m_thing->TestThis();
    }
};

///////////////////////////////////////////////////////////////////////////
// интерфейс репозитория
class IRepository
{
public:
    virtual string Save()=0;
};

///////////////////////////////////////////////////////////////////////////
// реализация репозитория - базы данных
class Repository : public IRepository
{
public:
    string Save()
    {
        return "I am saving data to Database.";
    }
};

///////////////////////////////////////////////////////////////////////////
// реализация текстового репозитория
class TextRepository : public IRepository
{
public:
    string Save()
    {
        return "I am saving data to TextFile.";
    }
};

/////////////////////////////////////////////////////////////////////////////
// интерфейс, через который должна происходить работа с репозиторием
class PurchaseBl
{
 private:
     IRepository* _repository;
 public:
     PurchaseBl(IRepository *repository)
     {
        _repository = repository;
     }
    string SavePurchaseOrder()
     {
        return _repository->Save();
     }
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

int main()
{

    //gContainer.RegisterFactory<IAmTheOtherThing, TheOtherThing, IAmAThing>(); // привязываем интерфейс, его реализацию и аргумент
    //gContainer.GetObject<IAmTheOtherThing>()->TheOtherTest();// вызываем тест IAmThing (ошибка в этом месте)
    // относительно данного интерфейса будет создан объект, зная объект, вызываем метод данного объекта

    //Создание зависимости
    IRepository *dbRepository = new Repository();

    //Внедрение зависимости
    PurchaseBl purchaseBl(dbRepository);
    cout<<purchaseBl.SavePurchaseOrder()<<endl;

    //Создание зависимости
    IRepository *textRepository = new TextRepository();

    //Внедрение зависимости
    PurchaseBl purchaseBlT(textRepository);
    cout<<purchaseBlT.SavePurchaseOrder()<<endl;

    // привязываем к IoC интерфейс репозитория и его реализацию
    gContainer.RegisterInstance<IRepository, Repository>();
    gContainer.RegisterInstance<IRepository, TextRepository>();

    // выдаём необходимое
    cout<<"From Container"<<endl;
    cout<<gContainer.GetObject<IRepository>()->Save()<<endl;

}

*/

#endif // IOCCONTAINER_H
