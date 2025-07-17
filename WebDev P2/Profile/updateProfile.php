<?php

include "../Functions.php";

session_start();
RedirectIfNoId('../Login');

include '../db.php';

$userId = $_SESSION['userId'];

// Username Change
if (!empty($_POST['username'])) {
    $newUsername = $_POST['username'];
    $stmt = $conn->prepare("UPDATE users SET username = ? WHERE id = ?");
    $stmt->bind_param("si", $newUsername, $userId);
    if ($stmt->execute()) {
        $_SESSION['username'] = $newUsername; // Update session username
        $_SESSION['message'] = "Username updated successfully.";
        $_SESSION['message_type'] = "success";
    } else {
        $_SESSION['message'] = "Error updating username.";
        $_SESSION['message_type'] = "error";
    }
    $stmt->close();
}

// Password Change
if (!empty($_POST['password'])) {
    if ($_POST['password'] === $_POST['password_confirmation']) {
        $newPasswordHash = password_hash($_POST['password'], PASSWORD_BCRYPT);
        $stmt = $conn->prepare("UPDATE users SET password = ? WHERE id = ?");
        $stmt->bind_param("si", $newPasswordHash, $userId);
        if ($stmt->execute()) {
            $_SESSION['message'] = "Password updated successfully.";
            $_SESSION['message_type'] = "success";

            if (isset($_COOKIE['remember_me'])) {
                unset($_COOKIE['remember_me']);
                setcookie('remember_me', '', time() - 3600, '/');
            }
            session_destroy();
            header("location: ../Login");
            exit;
        } else {
            $_SESSION['message'] = "Error updating password.";
            $_SESSION['message_type'] = "error";
        }
        $stmt->close();
    } else {
        $_SESSION['message'] = "Passwords do not match.";
        $_SESSION['message_type'] = "error";
    }
}
header("location: ../index.php");
exit();
?>
