package com.example.demo.controller;

public class result {
	public result() {
		
	}
	public result(Integer rating, float avgage) {
		super();
	    this.rating = rating;
	    this.avgage = avgage;
	}
	public int rating;
	public float avgage;

	    
	   //getters and setters
	 
	@Override
	public String toString() {
		return "result [rating=" + rating + ", avgage=" + avgage + "]";
	}
}
