/*
We have to develop a coffee machine with TDD. The machine uses the automated source of ingredients, which implements the interface ISourceOfIngredients.

Our machine should be able to produce the coffee accordingly to the next receipts:
- americano: water & coffee 1:2 or 1:3. Water temp 60C
- cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
- latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
- marochino - chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty

We have 2 possible sizes of the cup:
- little 100 gram
- big 140 gram

Implement worked coffee machine using ISourceOfIngredients to controll the process of coffee production.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>



class ISourceOfIngredients
{
public:
    virtual ~ISourceOfIngredients() {}
    virtual void SetCupSize(int gram) = 0;
    virtual void AddWater(int gram, int temperature) = 0;
    virtual void AddSugar(int gram) = 0;
    virtual void AddCoffee(int gram) = 0;
    virtual void AddMilk(int gram) = 0;
    virtual void AddMilkFoam(int gram) = 0;
    virtual void AddChocolate(int gram) = 0;
    virtual void AddCream(int gram) = 0;
};

class MockSourceOfIngredients : public ISourceOfIngredients
{
    void SetCupSize(int gram){};
    void AddWater(int gram, int temperature){};
    void AddSugar(int gram){};
    void AddCoffee(int gram){};
    void AddMilk(int gram){};
    void AddMilkFoam(int gram){};
    void AddChocolate(int gram){};
    void AddCream(int gram){};
};

class Cofee
{
public:
    void fillIngredients(ISourceOfIngredients* source)
    {
        m_source.reset(source);
    }

    virtual ~Cofee(){}
    virtual const std::string drink() = 0;

private:
    std::unique_ptr<ISourceOfIngredients> m_source;
};

class Americano : public Cofee
{
public:
    const std::string drink()
    {
        return "Americano";
    }
};

class Latte : public Cofee
{
public:
    const std::string drink()
    {
        return "Latte";
    }
};

class Cappuccino : public Cofee
{
public:
    const std::string drink()
    {
        return "Cappuccino";
    }
};

class Marochino : public Cofee
{
public:
    const std::string drink()
    {
        return "Marochino";
    }
};

TEST(CofeeTest, check_that_drink_marochino)
{
    Marochino mar;
    EXPECT_EQ(mar.drink(), "Marochino");
}

TEST(CofeeTest, check_that_drink_americano)
{
    Americano amer;
    EXPECT_EQ(amer.drink(), "Americano");
}

TEST(CofeeTest, check_that_drink_latte)
{
    Latte lat;
    EXPECT_EQ(lat.drink(), "Latte");
}

TEST(CofeeTest, check_that_drink_cappuccino)
{
    Cappuccino cap;
    EXPECT_EQ(cap.drink(), "Cappuccino");
}
