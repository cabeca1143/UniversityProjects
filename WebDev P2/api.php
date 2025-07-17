<?php
session_start();

if (!isset($_SESSION['userId'])) {
    http_response_code(401);
    exit();
}

$userId = $_SESSION['userId'];

require "db.php";

header("Content-Type: application/json; charset=UTF-8");

$method = $_SERVER['REQUEST_METHOD'];

if ($method === 'GET') {
    $stmt = $conn->prepare("SELECT `user-data` FROM users WHERE id = ?");
    $stmt->bind_param("i", $userId);
    $stmt->execute();
    $result = $stmt->get_result();
    $user = $result->fetch_assoc();

    $reviews = [];
    if ($user && $user['user-data']) {
        $reviews = json_decode($user['user-data'], true);
    }

    foreach ($reviews as &$review) {
        $protocol = (!empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off') ? "https" : "http";
        $host = $_SERVER['HTTP_HOST'];
        $imageUrl = "{$protocol}://{$host}/Uploads/{$review['image']}";
        $review['image'] = $imageUrl;
        unset($review);
    }

    $updatedReviewsJson = json_encode($reviews);

    if ($updatedReviewsJson) {
        echo $updatedReviewsJson;
    } else {
        echo json_encode([]);
    }
    $stmt->close();

} elseif ($method === 'POST') {
    if(isset($_POST['delete']))
    {
        DeleteReview($conn, $userId);
    }elseif (isset($_POST['title']))
    {
        ProcessReview($conn, $userId);
    }else
    {
        http_response_code(400);
        echo json_encode(["error" => "Invalid request"]);
        exit();
    }
}

function ProcessReview($conn, $userId)
{
    try {
        if(isset($_POST['id']))
        {
            UpdateReview($conn, $userId);
        }
        else
        {
            HandleFile();
            CreateReview($conn, $userId);
        }
    } catch (Exception $e) {
        $conn->rollback();
        http_response_code(500);
        echo json_encode(["error" => "Failed to update data: " . $e->getMessage()]);
    }
}

function UpdateReview($conn, $userId)
{
    $conn->begin_transaction();
    $stmt = $conn->prepare("SELECT `user-data` FROM users WHERE id = ? FOR UPDATE");
    $stmt->bind_param("i", $userId);
    $stmt->execute();
    $result = $stmt->get_result();
    $user = $result->fetch_assoc();

    $reviews = [];
    if ($user && $user['user-data']) {
        $reviews = json_decode($user['user-data'], true);
    }
    $toChange = $reviews[count($reviews) - $_POST['id']];
    $reviews[count($reviews) - $_POST['id']] = [
        'title' => $_POST['title'] ?? $toChange['title'],
        'rating' => $_POST['rating'] ?? $toChange['rating'],
        'image' => $toChange['image'],
        'description' => $_POST['description'] ?? $toChange['description']
    ];
        $updatedReviewsJson = json_encode($reviews);

        $updateStmt = $conn->prepare("UPDATE users SET `user-data` = ? WHERE id = ?");
        $updateStmt->bind_param("si", $updatedReviewsJson, $userId);
        $updateStmt->execute();

        $conn->commit();

        http_response_code(201);
        echo json_encode($reviews[$_POST['id']]);
}

function CreateReview($conn, $userId)
{
    $conn->begin_transaction();
    $stmt = $conn->prepare("SELECT `user-data` FROM users WHERE id = ? FOR UPDATE");
    $stmt->bind_param("i", $userId);
    $stmt->execute();
    $result = $stmt->get_result();
    $user = $result->fetch_assoc();

    $reviews = [];
    if ($user && $user['user-data']) {
        $reviews = json_decode($user['user-data'], true);
    }

    $newReview = [
        'title' => $_POST['title'],
        'rating' => $_POST['rating'],
        'image' => !empty($_FILES['image']['name']) ? $_FILES['image']['name'] : null,
        'description' => $_POST['description'] ?? '',
    ];
    array_unshift($reviews, $newReview);

    $updatedReviewsJson = json_encode($reviews);

    $updateStmt = $conn->prepare("UPDATE users SET `user-data` = ? WHERE id = ?");
    $updateStmt->bind_param("si", $updatedReviewsJson, $userId);
    $updateStmt->execute();

    $conn->commit();

    http_response_code(201);
    echo json_encode($newReview);
}

function HandleFile()
{
    if(!isset($_FILES['image']))
    {
        return;
    }

    $uploadDir = 'Uploads/';
    if (!is_dir($uploadDir)) {
        mkdir($uploadDir, 0755, true);
    }

    $fileTmpPath = $_FILES['image']['tmp_name'];
    $fileName = $_FILES['image']['name'];

    $safeFileName = uniqid() . '-' . basename($fileName);
    $_FILES['image']['name'] = $safeFileName;
    $destination = $uploadDir . $safeFileName;

    move_uploaded_file($fileTmpPath, $destination);
}

function DeleteReview($conn, $userId)
{
    $conn->begin_transaction();
    $stmt = $conn->prepare("SELECT `user-data` FROM users WHERE id = ? FOR UPDATE");
    $stmt->bind_param("i", $userId);
    $stmt->execute();
    $result = $stmt->get_result();
    $user = $result->fetch_assoc();

    $reviews = [];
    if ($user && $user['user-data']) {
        $reviews = json_decode($user['user-data'], true);
    }

    $index = sizeof($reviews) - $_POST['delete'];
    if (isset($reviews[$index])) {
        array_splice($reviews, $index, 1);
    } else {
        throw new Exception("Review index not found.");
    }
    $updatedReviewsJson = json_encode(array_values($reviews));

    $updateStmt = $conn->prepare("UPDATE users SET `user-data` = ? WHERE id = ?");
    $updateStmt->bind_param("si", $updatedReviewsJson, $userId);
    $updateStmt->execute();

    $conn->commit();

    http_response_code(201);
    echo json_encode($reviews[$_POST->id]);
}
$conn->close();
?>
