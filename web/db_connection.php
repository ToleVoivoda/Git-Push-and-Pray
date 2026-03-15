<?php
 
    $host="localhost";
    $port=3306;
    $user="root";
    $password="";
    $dbname="streets";

    $con = new mysqli($host, $user, $password, $dbname, $port);
    //    or die ('Could not connect to the database server' . mysqli_connect_error());
    if(!$con)
    {
        header("Location: login.html?не бачкам");
        exit();
    }
 
    //$con->close();