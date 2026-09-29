const spaceCanvas = document.getElementById("spaceCanvas");
const spaceContext = spaceCanvas.getContext("2d");


// ============================================================
// SPACE CONFIGURATION
// ============================================================

const STAR_COUNT = 120;

let stars = [];

let mouseX = 0;
let mouseY = 0;

let targetMouseX = 0;
let targetMouseY = 0;


// ============================================================
// CANVAS SIZE
// ============================================================

function resizeSpaceCanvas()
{
    spaceCanvas.width = window.innerWidth;
    spaceCanvas.height = window.innerHeight;
}


// ============================================================
// STAR CREATION
// ============================================================

function createStars()
{
    stars = [];

    for (let i = 0; i < STAR_COUNT; i++)
    {
        stars.push({

            x:
                Math.random()
                * spaceCanvas.width,

            y:
                Math.random()
                * spaceCanvas.height,


            size:
                Math.random() * 1.4
                + 0.2,


            baseOpacity:
                Math.random() * 0.35
                + 0.08,


            opacity:
                0.2,


            speedX:
                (Math.random() - 0.5)
                * 0.08,


            speedY:
                (Math.random() - 0.5)
                * 0.08,


            twinkleSpeed:
                Math.random()
                * 0.015
                + 0.005,


            twinkleOffset:
                Math.random()
                * Math.PI
                * 2,


            depth:
                Math.random()
        });
    }
}


// ============================================================
// NEBULA
// ============================================================

function drawNebula(
    x,
    y,
    radius,
    red,
    blue,
    alpha
)
{
    const gradient =
        spaceContext.createRadialGradient(
            x,
            y,
            0,
            x,
            y,
            radius
        );


    gradient.addColorStop(
        0,
        `rgba(${red}, ${blue}, ${blue}, ${alpha})`
    );


    gradient.addColorStop(
        1,
        "rgba(0, 0, 0, 0)"
    );


    spaceContext.fillStyle = gradient;


    spaceContext.beginPath();

    spaceContext.arc(
        x,
        y,
        radius,
        0,
        Math.PI * 2
    );

    spaceContext.fill();
}


// ============================================================
// DRAW STARS
// ============================================================

function drawStars(time)
{
    for (const star of stars)
    {
        // ----------------------------------------------------
        // Movement
        // ----------------------------------------------------

        star.x += star.speedX;
        star.y += star.speedY;


        // ----------------------------------------------------
        // Screen wrapping
        // ----------------------------------------------------

        if (star.x < -5)
        {
            star.x =
                spaceCanvas.width + 5;
        }


        if (star.x >
            spaceCanvas.width + 5)
        {
            star.x = -5;
        }


        if (star.y < -5)
        {
            star.y =
                spaceCanvas.height + 5;
        }


        if (star.y >
            spaceCanvas.height + 5)
        {
            star.y = -5;
        }


        // ----------------------------------------------------
        // Twinkle
        // ----------------------------------------------------

        const twinkle =
            Math.sin(
                time * star.twinkleSpeed
                + star.twinkleOffset
            );


        star.opacity =
            star.baseOpacity
            + twinkle * 0.08;


        // ----------------------------------------------------
        // Mouse parallax
        // ----------------------------------------------------

        const parallaxX =
            mouseX
            * star.depth
            * 10;


        const parallaxY =
            mouseY
            * star.depth
            * 10;


        const drawX =
            star.x + parallaxX;


        const drawY =
            star.y + parallaxY;


        // ----------------------------------------------------
        // Draw
        // ----------------------------------------------------

        spaceContext.beginPath();


        spaceContext.arc(
            drawX,
            drawY,
            star.size,
            0,
            Math.PI * 2
        );


        spaceContext.fillStyle =
            `rgba(
                255,
                255,
                255,
                ${Math.max(0.02, star.opacity)}
            )`;


        spaceContext.fill();


        // ----------------------------------------------------
        // Rare bright stars
        // ----------------------------------------------------

        if (star.size > 1.25)
        {
            spaceContext.beginPath();

            spaceContext.arc(
                drawX,
                drawY,
                star.size * 2.5,
                0,
                Math.PI * 2
            );


            const glow =
                spaceContext.createRadialGradient(
                    drawX,
                    drawY,
                    0,
                    drawX,
                    drawY,
                    star.size * 2.5
                );


            glow.addColorStop(
                0,
                `rgba(255, 255, 255, ${star.opacity * 0.25})`
            );


            glow.addColorStop(
                1,
                "rgba(255, 255, 255, 0)"
            );


            spaceContext.fillStyle = glow;

            spaceContext.fill();
        }
    }
}


// ============================================================
// SPACE RENDER LOOP
// ============================================================

function drawSpace(time)
{
    // --------------------------------------------------------
    // Background
    // --------------------------------------------------------

    spaceContext.clearRect(
        0,
        0,
        spaceCanvas.width,
        spaceCanvas.height
    );


    // --------------------------------------------------------
    // Deep space gradient
    // --------------------------------------------------------

    const background =
        spaceContext.createRadialGradient(
            spaceCanvas.width * 0.5,
            spaceCanvas.height * 0.35,
            0,

            spaceCanvas.width * 0.5,
            spaceCanvas.height * 0.5,
            Math.max(
                spaceCanvas.width,
                spaceCanvas.height
            )
        );


    background.addColorStop(
        0,
        "#0b0a10"
    );


    background.addColorStop(
        0.5,
        "#050507"
    );


    background.addColorStop(
        1,
        "#010102"
    );


    spaceContext.fillStyle = background;


    spaceContext.fillRect(
        0,
        0,
        spaceCanvas.width,
        spaceCanvas.height
    );


    // --------------------------------------------------------
    // Nebula
    // --------------------------------------------------------

    const nebulaTime =
        time * 0.00003;


    const nebulaX =
        spaceCanvas.width * 0.25
        + Math.sin(nebulaTime) * 80;


    const nebulaY =
        spaceCanvas.height * 0.3
        + Math.cos(nebulaTime) * 50;


    drawNebula(
        nebulaX,
        nebulaY,
        350,
        255,
        38,
        0.035
    );


    const nebulaX2 =
        spaceCanvas.width * 0.75
        + Math.cos(nebulaTime * 0.7) * 100;


    const nebulaY2 =
        spaceCanvas.height * 0.7
        + Math.sin(nebulaTime * 0.7) * 60;


    drawNebula(
        nebulaX2,
        nebulaY2,
        300,
        70,
        90,
        0.025
    );


    // --------------------------------------------------------
    // Mouse smoothing
    // --------------------------------------------------------

    mouseX +=
        (targetMouseX - mouseX)
        * 0.02;


    mouseY +=
        (targetMouseY - mouseY)
        * 0.02;


    // --------------------------------------------------------
    // Stars
    // --------------------------------------------------------

    drawStars(time);


    requestAnimationFrame(drawSpace);
}


// ============================================================
// MOUSE PARALLAX
// ============================================================

window.addEventListener(
    "mousemove",
    (event) =>
    {
        targetMouseX =
            event.clientX
            / window.innerWidth
            - 0.5;


        targetMouseY =
            event.clientY
            / window.innerHeight
            - 0.5;
    }
);


// ============================================================
// WINDOW RESIZE
// ============================================================

window.addEventListener(
    "resize",
    () =>
    {
        resizeSpaceCanvas();
        createStars();
    }
);


// ============================================================
// INITIALIZATION
// ============================================================

resizeSpaceCanvas();

createStars();

requestAnimationFrame(drawSpace);