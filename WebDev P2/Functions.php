<?php

function RedirectIfNoId($redirectPath)
{
    CheckCookie();
    if (!isset($_SESSION['userId'])) {
        header('Location: ' .  $redirectPath);
        exit();
    }
}

function RedirectIfId($redirectPath)
{
    CheckCookie();
    if (isset($_SESSION['userId'])) {
        header('Location: ' .  $redirectPath);
        exit();
    }
}

function CheckCookie()
{
    if (isset($_COOKIE['remember_me'])) {
        require "db.php";

        if (!$conn->connect_error)
        {
            list($userId, $token) = explode(':', $_COOKIE['remember_me'], 2);
            $hashed_token = hash('sha256', $token);

            $stmt = $conn->prepare("SELECT id, username FROM users WHERE id = ? AND remember_token = ?");
            $stmt->bind_param("is", $userId, $hashed_token);
            $stmt->execute();
            $result = $stmt->get_result();

            if ($result->num_rows === 1) {
                $user = $result->fetch_assoc();

                session_regenerate_id(true);
                $_SESSION['userId'] = $user['id'];
                $_SESSION['username'] = $user['username'];
            }
            $stmt->close();
            $conn->close();
        }
    }
}