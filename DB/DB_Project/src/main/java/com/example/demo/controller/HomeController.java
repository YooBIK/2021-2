package com.example.demo.controller;
 
import java.util.ArrayList;
import java.util.List;
import java.sql.*;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
 
@RestController
public class HomeController {
    
	/*
    @RequestMapping(value="/")
    public String index() {
        
        return "index";
    }
    */
	@RequestMapping(value="/step1") //http://localhost:8000/step1
	 public List<result> getResult() throws SQLException {
	      List<result> resultList = new ArrayList<result>();
	      try (Connection conn = DriverManager.getConnection("jdbc:mariadb://localhost/jdbc_connection_practice", "root",""
	        		+ "zkdlsem1")) {
	            // create a Statement
	            try (Statement stmt = conn.createStatement()) {
	            	 //사용될 쿼리를 String자료형으로 저장
	            	String sql= "SELECT S.rating, AVG(S.age) AS avgage "
	            			+ "FROM sailors S "
	            			+ "WHERE S.age>=18 "
	            			+ "GROUP BY S.rating "
	            			+ "HAVING 1<(SELECT COUNT(*) FROM sailors S2 WHERE S.rating=S2.rating AND S2.age>=18)";
	                //execute query
	            	try (ResultSet rs = stmt.executeQuery(sql)) {
	            		while(rs.next()) {
	            			resultList.add(new result(rs.getInt("rating"),rs.getFloat("avgage")));
	            		}
	            		
	                }
	            }   
            	
	      }
          return resultList;
	 }

}
