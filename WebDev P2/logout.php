<?php

session_start();

$_SESSION = array();

if (isset($_COOKIE['remember_me'])) {
    unset($_COOKIE['remember_me']);
    setcookie('remember_me', '', time() - 3600, '/');
}
session_destroy();
header("location: ../Login");
exit;

