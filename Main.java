package com.timbuchalka;


import com.Healthyburger;

public class Main {

    public static void main(String[] args) {


        Hamburger hamburger = new Hamburger("basic","white",5,"turkey");

        hamburger.addAddition1("chip",1);
        hamburger.addAddition2("cheese",0.75);
        hamburger.addAddition3("lettuce",0.23);
        hamburger.addAddition4("potato",1.1);

        hamburger.itemizeHamburger();

        Healthyburger healthyburger = new Healthyburger("gray",5.5);

    }
}
