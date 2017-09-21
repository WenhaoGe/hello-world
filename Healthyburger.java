package com;

import com.timbuchalka.Hamburger;

public class Healthyburger extends Hamburger {

    private String additionextra1Name;
    private double additionextra1Price;

    private String additionextra2Name;
    private double additionextra2Price;

    public Healthyburger(String breadRollType, double price) {
        super("sausage", breadRollType, price,"bacon");
    }



}
