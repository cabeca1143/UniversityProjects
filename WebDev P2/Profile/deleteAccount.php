<?php

include("../Functions.php");

session_start();

RedirectIfNoId('../Login');

require '../db.php';

$userId = $_SESSION['userId'];

$stmt = $conn->prepare("DELETE FROM users WHERE id = ?");
$stmt->bind_param("i", $userId);

$stmt->execute();
$stmt->close();
$conn->close();

require "../logout.php";
exit();