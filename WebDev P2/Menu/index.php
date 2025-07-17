<?php

include "../Functions.php";

session_start();

RedirectIfNoId("../Login");

$username = htmlspecialchars($_SESSION['username']);
require "../Head.php";
?>

<title>Profile</title>
<head/>

<body style="min-height: 100vh">

    <?php
        require "../TopBar.php";
    ?>

    <main class="container py-5">
        <div id="reviews-container" class="row g-4"></div>
    </main>

    <div class="floating-add-btn" data-bs-toggle="modal" data-bs-target="#addReviewModal">
        <i class="fas fa-plus"></i>
    </div>

    <div class="modal fade" id="addReviewModal" tabindex="-1" aria-labelledby="addReviewModalLabel" aria-hidden="true">
        <div class="modal-dialog modal-dialog-centered">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title" id="addReviewModalLabel">Add a New Review</h5>
                    <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                </div>
                <div class="modal-body">
                    <form id="reviewForm">
                        <div class="mb-3">
                            <label for="reviewTitle" class="form-label">Title</label>
                            <input type="text" class="form-control" id="reviewTitle" required>
                        </div>
                        <div class="mb-3">
                            <label for="reviewImage" class="form-label">Image (Optional)</label>
                            <input type="file" class="form-control" id="reviewImage" accept="image/*">
                        </div>
                        <div class="mb-3">
                            <label class="form-label">Rating</label>
                            <div class="star-rating">
                                <input type="radio" id="star5" name="rating" value="5" /><label for="star5" title="5 stars"><i class="fas fa-star"></i></label>
                                <input type="radio" id="star4" name="rating" value="4" /><label for="star4" title="4 stars"><i class="fas fa-star"></i></label>
                                <input type="radio" id="star3" name="rating" value="3" /><label for="star3" title="3 stars"><i class="fas fa-star"></i></label>
                                <input type="radio" id="star2" name="rating" value="2" /><label for="star2" title="2 stars"><i class="fas fa-star"></i></label>
                                <input type="radio" id="star1" name="rating" value="1" required/><label for="star1" title="1 star"><i class="fas fa-star"></i></label>
                            </div>
                        </div>
                        <div class="mb-3">
                            <label for="reviewDescription" class="form-label">Comment (Optional)</label>
                            <textarea class="form-control" id="reviewDescription" rows="4"></textarea>
                        </div>
                    </form>
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>
                    <button type="button" class="btn btn-primary" id="submitReview">Save Review</button>
                </div>
            </div>
        </div>
    </div>

    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js"></script>
    <script src="main.js"></script>
</body>
</html>
