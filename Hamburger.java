package com.timbuchalka;

public class Hamburger {
    private String name;
    private String breadRollType;
    private double price;
    private String meat;

    private String addition1;
    private double addition1price;

    private String addition2;
    private double addition2price;

    private String addition3;
    private double addition3price;

    private String addition4;
    private double addition4price;


    public Hamburger(String name, String breadRollType, double price, String meat) {
        this.name = name;
        this.breadRollType = breadRollType;
        this.price = price;
        this.meat = meat;
    }

    public void addAddition1(String name, double price){
        this.addition1 = name;
        this.addition1price = price;
    }
    public void addAddition2(String name, double price){
        this.addition2 = name;
        this.addition2price = price;
    }
    public void addAddition3(String name, double price){
        this.addition3 = name;
        this.addition3price = price;
    }
    public void addAddition4(String name, double price){
        this.addition4 = name;
        this.addition4price = price;
    }

    public double itemizeHamburger(){

        double hamburgerPrice = this.price;

        System.out.println(this.name + "hamburger has " +breadRollType +" bread roll type " + this.meat+" as meat and price is " +this.price );
        if(this.addition1 != null) {
            hamburgerPrice += this.addition1price;
            System.out.println("Added " + this.addition1 + " for an extra " + this.addition1price);
        }

        if(this.addition2 != null) {
            hamburgerPrice += this.addition2price;
            System.out.println("Added " + this.addition2 + " for an extra " + this.addition2price);
        }
        if(this.addition3 != null) {
            hamburgerPrice += this.addition3price;
            System.out.println("Added " + this.addition3 + " for an extra " + this.addition3price);
        }

        if(this.addition4 != null) {
            hamburgerPrice += this.addition4price;
            System.out.println("Added " + this.addition4 + " for an extra " + this.addition4price);
        }

        double totalPrice = hamburgerPrice + this.addition1price + this.addition2price + this.addition3price + this.addition4price;
        System.out.println("The total price is "+ totalPrice);

        return hamburgerPrice;

    }



}
