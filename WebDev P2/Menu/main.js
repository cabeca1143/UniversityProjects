document.addEventListener('DOMContentLoaded', function () {
    const API_URL = '../api.php';

    const reviewsContainer = document.getElementById('reviews-container');
    const submitBtn = document.getElementById('submitReview');
    const reviewForm = document.getElementById('reviewForm');
    const addReviewModalEl = document.getElementById('addReviewModal');
    const reviewModal = new bootstrap.Modal(addReviewModalEl);

    modalCounter = 0;
    const renderReviewCard = (reviewData) => {
        const { title, rating, description, image } = reviewData;
        //Process the star rating HTML
        let stars = '';
        for (let i = 0; i < rating; i++) {
            stars += `<i class="fa fa-star ${i < rating ? 'text-warning' : ''}"></i>`;
        }

        //Initialize HTML Object
        const cardColumn = document.createElement('div');
        cardColumn.className = 'col-lg-4 col-md-6 col-sm-12';
        cardColumn.innerHTML = `
            <div class="card h-100">
                <div class="floating-add-btn" data-bs-toggle="modal" data-bs-target="#editReviewModal${modalCounter}">
                    <i class="fa fa-pencil fa-fw"></i>
                </div>
                <img src="${image == null || image == "null" ? 'https://placehold.co/600x400/333/FFF?text=No+Image' : image}" 
                     class="card-img-top" 
                     alt="${title}" 
                     onerror="this.onerror=null;
                     this.src='https://placehold.co/600x400/333/FFF?text=Invalid+Image';">
                <div class="card-body d-flex flex-column">
                    <h5 class="card-title" style="color: white;">${title}</h5>
                    <p class="card-text text-warning mb-2">${stars}</p>
                    <p class="card-text flex-grow-1" style="color: white;">${description || ''}</p>
                </div>
            </div>
            <!-- This is Horrible -->
            <div class="modal fade" id="editReviewModal${modalCounter}" tabindex="-1" aria-labelledby="editReviewModalLabel${modalCounter}" aria-hidden="true">
                    <div class="modal-dialog modal-dialog-centered">
                        <div class="modal-content">
                            <div class="modal-header">
                                <h5 class="modal-title" id="addReviewModalLabel${modalCounter}">Edit Review</h5>
                                <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                            </div>
                            <div class="modal-body">
                                <form id="reviewForm">
                                    <div class="mb-3">
                                        <label for="reviewTitle${modalCounter}" class="form-label">Title</label>
                                        <input type="text" class="form-control" id="reviewTitle${modalCounter}" value="${title}">
                                    </div>
                                    <div class="mb-3">
                                        <label class="form-label">Rating</label>
                                        <div class="star-rating">
                                            <input type="radio" id="star5${modalCounter}" name="rating${modalCounter}" value="5" /><label for="star5${modalCounter}" title="5 stars"><i class="fas fa-star"></i></label>
                                            <input type="radio" id="star4${modalCounter}" name="rating${modalCounter}" value="4" /><label for="star4${modalCounter}" title="4 stars"><i class="fas fa-star"></i></label>
                                            <input type="radio" id="star3${modalCounter}" name="rating${modalCounter}" value="3" /><label for="star3${modalCounter}" title="3 stars"><i class="fas fa-star"></i></label>
                                            <input type="radio" id="star2${modalCounter}" name="rating${modalCounter}" value="2" /><label for="star2${modalCounter}" title="2 stars"><i class="fas fa-star"></i></label>
                                            <input type="radio" id="star1${modalCounter}" name="rating${modalCounter}" value="1" required/><label for="star1${modalCounter}" title="1 star"><i class="fas fa-star"></i></label>
                                        </div>
                                    </div>
                                    <div class="mb-3">
                                        <label for="reviewDescription${modalCounter}" class="form-label">Comment</label>
                                        <textarea class="form-control" id="reviewDescription${modalCounter}" rows="4">${description}</textarea>
                                    </div>
                                </form>
                            </div>
                            <div class="modal-footer">
                                <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>
                                <button type="button" class="btn btn-primary" id="updateReview${modalCounter}">Update Review</button>
                                <button type="button" class="btn btn-primary" id="deleteReview${modalCounter}" style="background-color: red; border: red">Delete Review</button>
                            </div>
                        </div>
                    </div>
                </div>
        `;
        reviewsContainer.prepend(cardColumn);

        const updateBtn = document.getElementById("updateReview" + modalCounter);
        const deleteBtn = document.getElementById("deleteReview" + modalCounter);
        deleteBtn.addEventListener('click', async function()
        {
            const id = parseInt(deleteBtn.id.replace(/\D/g,'')) + 1;
            const formData = new FormData();
            formData.append('delete', id);
            const response = await fetch(API_URL, {
                method: 'POST',
                body: formData,
            });

            if (!response.ok) throw new Error('Failed to delete review.');

            await loadReviews();

            //Hack, the modal isn't getting removed FSR
            const backdrop = document.querySelector('.modal-backdrop');
            if (backdrop) {
                backdrop.remove();
            }
            document.body.classList.remove('modal-open');
            reviewForm.reset();
            reviewModal.hide();
        });

        updateBtn.addEventListener('click', async function()
        {
            event.preventDefault();

            let id = parseInt(deleteBtn.id.replace(/\D/g,''));
            const title = document.getElementById('reviewTitle' + id).value;
            const rating = document.querySelector(`input[name="rating${id}"]:checked`)?.value;
            const description = document.getElementById('reviewDescription'+ id).value;

            if (!title || !rating) {
                alert('Please provide a title and a rating.');
                return;
            }
            id++;
            const formData = new FormData();
            formData.append('id', id);
            formData.append('title', title);
            formData.append('rating', Number(rating));
            formData.append('description', description);

            const response = await fetch(API_URL, {
                method: 'POST',
                body: formData,
            });

            if (!response.ok) throw new Error('Failed to edit review.');

            await loadReviews();

            //Hack, the modal isn't getting removed FSR
            const backdrop = document.querySelector('.modal-backdrop');
            if (backdrop) {
                backdrop.remove();
            }
            document.body.classList.remove('modal-open');
            reviewForm.reset();
            reviewModal.hide();
        });
        modalCounter++;
    };

    //Loads the card/review data from database
    const loadReviews = async () => {
        try {
            const response = await fetch(API_URL);
            if (!response.ok) {
                if (response.status === 401) {
                    window.location.href = 'login_page.php';
                }
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            const reviews = await response.json();

            reviewsContainer.innerHTML = '';
            if (reviews.length === 0) {
                reviewsContainer.innerHTML = '<p class="text-center">You have no reviews yet. Click the \'+\' button to add one!</p>';
            } else {
                modalCounter = 0;
                reviews.reverse().forEach(renderReviewCard);
            }
        } catch (error) {
            console.error("Error fetching reviews:", error);
            reviewsContainer.innerHTML = '<p class="text-danger text-center">Could not load reviews.</p>';
        }
    };

    // Handle form submission
    submitBtn.addEventListener('click', async function () {
        const title = document.getElementById('reviewTitle').value;
        const image = document.getElementById('reviewImage').files[0];
        const rating = document.querySelector('input[name="rating"]:checked')?.value;
        const description = document.getElementById('reviewDescription').value;

        if (!title || !rating) {
            alert('Please provide a title and a rating.');
            return;
        }

        const formData = new FormData();

        formData.append('title', title);
        formData.append('rating', Number(rating));
        formData.append('description', description);
        if (image) {
            formData.append('image', image);
        }

        try {
            const response = await fetch(API_URL, {
                method: 'POST',
                body: formData,
            });

            if (!response.ok) throw new Error('Failed to save review.');

            const newReview = await response.json();

            if (reviewsContainer.querySelector('p')) {
                reviewsContainer.innerHTML = '';
            }

            renderReviewCard(newReview);
            loadReviews(); //hack
            reviewForm.reset();
            reviewModal.hide();

        } catch (error) {
            console.error('Error saving review:', error);
            alert('Could not save your review. Please try again.');
        }
    });

    loadReviews();
});
