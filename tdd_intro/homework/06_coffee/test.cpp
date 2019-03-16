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
public:
    MOCK_METHOD1(SetCupSize, void(int));
    MOCK_METHOD2(AddWater, void(int, int));
    MOCK_METHOD1(AddSugar, void(int));
    MOCK_METHOD1(AddCoffee, void(int));
    MOCK_METHOD1(AddMilk, void(int));
    MOCK_METHOD1(AddMilkFoam, void(int));
    MOCK_METHOD1(AddChocolate, void(int));
    MOCK_METHOD1(AddCream, void(int));
};

class Cofee
{
public:
    void fillIngredients(std::unique_ptr<ISourceOfIngredients> source)
    {
        m_source.swap(source);
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

class CoffeeMachine
{
public:
    std::unique_ptr<Cofee> createSmallAmericano(std::unique_ptr<ISourceOfIngredients>& source)
    {
        std::unique_ptr<Cofee> cofee(new Americano);
        source->AddCoffee(30);
        source->AddWater(100, 60);
        cofee->fillIngredients(std::move(source));

        return std::move(cofee);
    }

    std::unique_ptr<Cofee> createSmallCappuccino(std::unique_ptr<ISourceOfIngredients>& source)
    {
        std::unique_ptr<Cofee> cofee(new Cappuccino);
        source->AddWater(100, 80);
        source->AddMilk(30);
        source->AddCoffee(30);
        source->AddMilkFoam(30);
        cofee->fillIngredients(std::move(source));

        return std::move(cofee);
    }

    std::unique_ptr<Cofee> createSmallLatte(std::unique_ptr<ISourceOfIngredients>& source)
    {
        std::unique_ptr<Cofee> cofee(new Latte);
        source->AddWater(100, 90);
        source->AddMilk(25);
        source->AddCoffee(50);
        source->AddMilkFoam(25);
        cofee->fillIngredients(std::move(source));

        return std::move(cofee);
    }

    std::unique_ptr<Cofee> createXXLLatte(std::unique_ptr<ISourceOfIngredients>& source)
    {
        std::unique_ptr<Cofee> cofee(new Latte);
        source->AddWater(100, 90);
        source->AddMilk(25);
        source->AddCoffee(50);
        source->AddMilkFoam(25);
        cofee->fillIngredients(std::move(source));

        return std::move(cofee);
    }

    std::unique_ptr<Cofee> createXXLAmericano(std::unique_ptr<ISourceOfIngredients>& source)
    {
        std::unique_ptr<Cofee> cofee(new Americano);
        source->AddCoffee(70);
        source->AddWater(140, 60);
        cofee->fillIngredients(std::move(source));

        return std::move(cofee);
    }

    std::unique_ptr<Cofee> createXXLCappuccino(std::unique_ptr<ISourceOfIngredients>& source)
    {
        std::unique_ptr<Cofee> cofee(new Cappuccino);
        source->AddWater(140, 80);
        source->AddMilk(45);
        source->AddCoffee(45);
        source->AddMilkFoam(45);
        cofee->fillIngredients(std::move(source));

        return std::move(cofee);
    }
};

TEST(CofeeMachine, create_XXL_latte)
{
    // latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(140, 90)).Times(1);
    EXPECT_CALL(*source, AddMilk(35)).Times(1);
    EXPECT_CALL(*source, AddCoffee(70)).Times(1);
    EXPECT_CALL(*source, AddMilkFoam(35)).Times(1);

    auto cofee = machine.createXXLLatte(ptr);

    EXPECT_EQ(cofee->drink(), "Latte");
}

TEST(CofeeMachine, create_small_latte)
{
    // latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(100, 90)).Times(1);
    EXPECT_CALL(*source, AddMilk(25)).Times(1);
    EXPECT_CALL(*source, AddCoffee(50)).Times(1);
    EXPECT_CALL(*source, AddMilkFoam(25)).Times(1);

    auto cofee = machine.createSmallLatte(ptr);

    EXPECT_EQ(cofee->drink(), "Latte");
}

TEST(CofeeMachine, create_XXL_cappuccino)
{
    //cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(140, 80)).Times(1);
    EXPECT_CALL(*source, AddMilk(45)).Times(1);
    EXPECT_CALL(*source, AddCoffee(45)).Times(1);
    EXPECT_CALL(*source, AddMilkFoam(45)).Times(1);

    auto cofee = machine.createXXLCappuccino(ptr);

    EXPECT_EQ(cofee->drink(), "Cappuccino");
}

TEST(CofeeMachine, create_small_cappuccino)
{
    //cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(100, 80)).Times(1);
    EXPECT_CALL(*source, AddMilk(30)).Times(1);
    EXPECT_CALL(*source, AddCoffee(30)).Times(1);
    EXPECT_CALL(*source, AddMilkFoam(30)).Times(1);

    auto cofee = machine.createSmallCappuccino(ptr);

    EXPECT_EQ(cofee->drink(), "Cappuccino");
}

TEST(CofeeMachine, create_XXL_americano)
{
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(140, 60)).Times(1);
    EXPECT_CALL(*source, AddCoffee(70)).Times(1);

    auto cofee = machine.createXXLAmericano(ptr);

    EXPECT_EQ(cofee->drink(), "Americano");
}

TEST(CofeeMachine, create_small_americano)
{
    CoffeeMachine machine;
    MockSourceOfIngredients* source = new MockSourceOfIngredients;
    std::unique_ptr<ISourceOfIngredients> ptr(source);
    EXPECT_CALL(*source, AddWater(100, 60)).Times(1);
    EXPECT_CALL(*source, AddCoffee(30)).Times(1);

    auto cofee = machine.createSmallAmericano(ptr);

    EXPECT_EQ(cofee->drink(), "Americano");
}

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
