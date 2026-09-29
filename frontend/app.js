const spaceCanvas = document.getElementById("spaceCanvas");
const spaceContext = spaceCanvas.getContext("2d");

let stars = [];

const STAR_COUNT = 90;


function resizeSpaceCanvas() {

    spaceCanvas.width = window.innerWidth;
    spaceCanvas.height = window.innerHeight;

}


function createStars() {

    stars = [];

    for (let i = 0; i < STAR_COUNT; i++) {

        stars.push({
            x: Math.random() * spaceCanvas.width,
            y: Math.random() * spaceCanvas.height,

            size: Math.random() * 1.4 + 0.3,

            speedX: (Math.random() - 0.5) * 0.12,
            speedY: (Math.random() - 0.5) * 0.12,

            opacity: Math.random() * 0.45 + 0.1
        });

    }

}


function drawStars() {

    spaceContext.clearRect(
        0,
        0,
        spaceCanvas.width,
        spaceCanvas.height
    );


    for (const star of stars) {

        star.x += star.speedX;
        star.y += star.speedY;


        if (star.x < 0) {
            star.x = spaceCanvas.width;
        }

        if (star.x > spaceCanvas.width) {
            star.x = 0;
        }

        if (star.y < 0) {
            star.y = spaceCanvas.height;
        }

        if (star.y > spaceCanvas.height) {
            star.y = 0;
        }


        spaceContext.beginPath();

        spaceContext.arc(
            star.x,
            star.y,
            star.size,
            0,
            Math.PI * 2
        );


        spaceContext.fillStyle =
            `rgba(255, 255, 255, ${star.opacity})`;

        spaceContext.fill();

    }


    requestAnimationFrame(drawStars);

}


window.addEventListener("resize", () => {

    resizeSpaceCanvas();
    createStars();

});


resizeSpaceCanvas();
createStars();
drawStars();