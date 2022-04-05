#include <bits/stdc++.h>
using namespace std;

class Gift {
protected:
    string name, giverName;
public:
    Gift() = default;
    Gift(const string &name, const string &giverName) : name(name),
                                                        giverName(giverName) {}
    virtual void offerGift(const string &receivedBy) {
        cout << "The gift named " << name
             << " was received by " << receivedBy
             << " thanks to the courtesy of " << giverName << ".\n";
    }
};

class GiftCard : public Gift {
private:
    int sum;
public:
    GiftCard() : Gift(), sum(0) {}
    GiftCard(const string &name, const string &giverName, int sum) :
            Gift(name, giverName), sum(sum) {}

    void offerGift(const string &receivedBy) override{
        cout << "Congratulations " << receivedBy << "! You received a gift card of "
             << sum << "$ from " << giverName << ".\n";
    }
};

class GiftHoliday : public Gift {
private:
    string location;
public:
    GiftHoliday(const string &name, const string &giverName, const string &location) :
            Gift(name, giverName), location(location) {}

    void offerGift(const string &receivedBy) override{
        cout << receivedBy << ", it's time to pack up! You will travel to " << location
             <<" for a free holiday, thanks to the gift from " << giverName << ".\n";
    }
};

class GiftFavouriteProduct : public Gift {
private:
    string category;
public:
    GiftFavouriteProduct(const string &name, const string &giverName, const string &category) :
            Gift(name, giverName), category(category) {}

    void offerGift(const string &receivedBy) override{
        cout << "Good news, " << receivedBy << "! You received something you like (" << category
             <<") as a gift from " << giverName << ".\n";
    }
};

int main(){
    Gift simpleGift("No Name", "Eleanor Roosevelt");
    GiftCard card("Andrei Popescu", "Popescu Miruna", 300);
    GiftHoliday holiday("Ibiza platita!", "Leonard Coste", "Ibiza, Spain");
    GiftFavouriteProduct phone("Pentru tine", "Costache Leurdean","Apple Products");
    simpleGift.offerGift("Ioan");
    card.offerGift("Persida");
    holiday.offerGift("Romeo");
    phone.offerGift("Caligula");

    return 0;
}