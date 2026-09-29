
// ============================================================
// NEURODIGIT
// FRONTEND CONTROLLER
// ============================================================


// ============================================================
// SPACE BACKGROUND
// ============================================================

const spaceCanvas =
    document.getElementById("spaceCanvas");


const spaceContext =
    spaceCanvas.getContext("2d");


const STAR_COUNT = 120;


let stars = [];


let mouseX = 0;

let mouseY = 0;


let targetMouseX = 0;

let targetMouseY = 0;


// ============================================================
// RESIZE SPACE CANVAS
// ============================================================

function resizeSpaceCanvas()
{
    spaceCanvas.width =
        window.innerWidth;


    spaceCanvas.height =
        window.innerHeight;
}


// ============================================================
// CREATE STARS
// ============================================================

function createStars()
{
    stars = [];


    for (
        let i = 0;
        i < STAR_COUNT;
        i++
    )
    {
        stars.push({

            x:
                Math.random()
                * spaceCanvas.width,

            y:
                Math.random()
                * spaceCanvas.height,

            size:
                Math.random()
                * 1.4
                + 0.2,

            baseOpacity:
                Math.random()
                * 0.35
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
// DRAW NEBULA
// ============================================================

function drawNebula(
    x,
    y,
    radius,
    red,
    green,
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
        `rgba(
            ${red},
            ${green},
            ${blue},
            ${alpha}
        )`
    );


    gradient.addColorStop(
        1,
        "rgba(0, 0, 0, 0)"
    );


    spaceContext.fillStyle =
        gradient;


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

        star.x +=
            star.speedX;


        star.y +=
            star.speedY;


        if (
            star.x < -5
        )
        {
            star.x =
                spaceCanvas.width + 5;
        }


        if (
            star.x >
            spaceCanvas.width + 5
        )
        {
            star.x = -5;
        }


        if (
            star.y < -5
        )
        {
            star.y =
                spaceCanvas.height + 5;
        }


        if (
            star.y >
            spaceCanvas.height + 5
        )
        {
            star.y = -5;
        }


        const twinkle =
            Math.sin(
                time
                * star.twinkleSpeed
                + star.twinkleOffset
            );


        star.opacity =
            star.baseOpacity
            + twinkle * 0.08;


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
                ${Math.max(
                    0.02,
                    star.opacity
                )}
            )`;


        spaceContext.fill();


        if (
            star.size > 1.25
        )
        {

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
                `rgba(
                    255,
                    255,
                    255,
                    ${star.opacity * 0.25}
                )`
            );


            glow.addColorStop(
                1,
                "rgba(255, 255, 255, 0)"
            );


            spaceContext.beginPath();


            spaceContext.arc(
                drawX,
                drawY,
                star.size * 2.5,
                0,
                Math.PI * 2
            );


            spaceContext.fillStyle =
                glow;


            spaceContext.fill();
        }
    }
}


// ============================================================
// SPACE RENDER LOOP
// ============================================================

function drawSpace(time)
{

    spaceContext.clearRect(
        0,
        0,
        spaceCanvas.width,
        spaceCanvas.height
    );


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


    spaceContext.fillStyle =
        background;


    spaceContext.fillRect(
        0,
        0,
        spaceCanvas.width,
        spaceCanvas.height
    );


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
        55,
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
        80,
        255,
        0.025
    );


    mouseX +=
        (
            targetMouseX
            - mouseX
        )
        * 0.02;


    mouseY +=
        (
            targetMouseY
            - mouseY
        )
        * 0.02;


    drawStars(time);


    requestAnimationFrame(
        drawSpace
    );
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
// SPACE RESIZE
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
// DRAWING CANVAS
// ============================================================

const drawingCanvas =
    document.getElementById(
        "drawingCanvas"
    );


const drawingContext =
    drawingCanvas.getContext("2d");


const startButton =
    document.getElementById(
        "startButton"
    );


const clearButton =
    document.getElementById(
        "clearButton"
    );


const predictionElement =
    document.getElementById(
        "prediction"
    );


const confidenceElement =
    document.getElementById(
        "confidence"
    );


const feedbackSection =
    document.getElementById(
        "feedbackSection"
    );


const feedbackOverlay =
    document.getElementById(
        "feedbackOverlay"
    );


const yesButton =
    document.getElementById(
        "yesButton"
    );


const noButton =
    document.getElementById(
        "noButton"
    );


const networkStatus =
    document.getElementById(
        "networkStatus"
    );


let isDrawing = false;


let currentPrediction = null;


// ============================================================
// INITIALIZE DRAWING CANVAS
// ============================================================

function initializeDrawingCanvas()
{
    drawingContext.fillStyle =
        "#020203";


    drawingContext.fillRect(
        0,
        0,
        drawingCanvas.width,
        drawingCanvas.height
    );


    drawingContext.lineCap =
        "round";


    drawingContext.lineJoin =
        "round";


    drawingContext.strokeStyle =
        "#ffffff";


    drawingContext.lineWidth =
        18;
}


// ============================================================
// GET CANVAS POSITION
// ============================================================

function getCanvasPosition(event)
{
    const rect =
        drawingCanvas.getBoundingClientRect();


    return {

        x:
            (
                event.clientX
                - rect.left
            )
            * drawingCanvas.width
            / rect.width,

        y:
            (
                event.clientY
                - rect.top
            )
            * drawingCanvas.height
            / rect.height

    };
}


// ============================================================
// START DRAWING
// ============================================================

function startDrawing(event)
{
    isDrawing = true;


    const position =
        getCanvasPosition(event);


    drawingContext.beginPath();


    drawingContext.moveTo(
        position.x,
        position.y
    );


    drawingCanvas.setPointerCapture(
        event.pointerId
    );
}


// ============================================================
// DRAW
// ============================================================

function draw(event)
{
    if (!isDrawing)
    {
        return;
    }


    const position =
        getCanvasPosition(event);


    drawingContext.lineTo(
        position.x,
        position.y
    );


    drawingContext.stroke();
}


// ============================================================
// STOP DRAWING
// ============================================================

function stopDrawing()
{
    if (!isDrawing)
    {
        return;
    }


    isDrawing = false;


    drawingContext.closePath();
}


// ============================================================
// POINTER EVENTS
// ============================================================

drawingCanvas.addEventListener(
    "pointerdown",
    startDrawing
);


drawingCanvas.addEventListener(
    "pointermove",
    draw
);


drawingCanvas.addEventListener(
    "pointerup",
    stopDrawing
);


drawingCanvas.addEventListener(
    "pointercancel",
    stopDrawing
);


// ============================================================
// CLEAR CANVAS
// ============================================================

function clearCanvas()
{
    drawingContext.fillStyle =
        "#020203";


    drawingContext.fillRect(
        0,
        0,
        drawingCanvas.width,
        drawingCanvas.height
    );


    predictionElement.textContent =
        "—";


    confidenceElement.textContent =
        "Waiting for input...";


    feedbackSection.classList.add(
        "hidden"
    );


    currentPrediction =
        null;


    resetNetwork();


    networkStatus.textContent =
        "NETWORK IDLE";


    networkStatus.classList.remove(
        "active"
    );
}


clearButton.addEventListener(
    "click",
    clearCanvas
);


// ============================================================
// CONVERT DRAWING TO 28×28
// ============================================================

function getPixels()
{
    const smallCanvas =
        document.createElement(
            "canvas"
        );


    smallCanvas.width = 28;

    smallCanvas.height = 28;


    const smallContext =
        smallCanvas.getContext(
            "2d"
        );


    smallContext.drawImage(
        drawingCanvas,

        0,
        0,
        28,
        28
    );


    const imageData =
        smallContext.getImageData(
            0,
            0,
            28,
            28
        );


    const pixels = [];


    for (
        let i = 0;
        i < imageData.data.length;
        i += 4
    )
    {

        const red =
            imageData.data[i];


        const green =
            imageData.data[i + 1];


        const blue =
            imageData.data[i + 2];


        const brightness =
            (
                red
                + green
                + blue
            )
            / 3;


        pixels.push(
            brightness / 255
        );
    }


    return pixels;
}


// ============================================================
// PREDICT DIGIT
// ============================================================

async function predictDigit()
{
    const pixels =
        getPixels();


    if (pixels.length !== 784)
    {
        console.error(
            "Invalid pixel count:",
            pixels.length
        );

        return;
    }


    predictionElement.textContent =
        "...";


    confidenceElement.textContent =
        "Neural network is thinking...";


    feedbackSection.classList.add(
        "hidden"
    );


    currentPrediction =
        null;


    networkStatus.textContent =
        "PROCESSING INPUT...";


    networkStatus.classList.add(
        "active"
    );


    resetNetwork();


    try
    {

        const response =
            await fetch(
                "/predict",
                {

                    method:
                        "POST",

                    headers:
                    {
                        "Content-Type":
                            "application/json"
                    },

                    body:
                        JSON.stringify({
                            pixels:
                                pixels
                        })

                }
            );


        const result =
            await response.json();


        if (!response.ok)
        {
            throw new Error(
                result.error
                ||
                "Prediction failed"
            );
        }


        currentPrediction =
            result.prediction;


        predictionElement.textContent =
            result.prediction;


        predictionElement.classList.remove(
            "prediction-active"
        );


        void predictionElement.offsetWidth;


        predictionElement.classList.add(
            "prediction-active"
        );


        const confidence =
            result.confidence
            * 100;


        confidenceElement.textContent =
            `Confidence: ${
                confidence.toFixed(2)
            }%`;


        feedbackSection.classList.remove(
            "hidden"
        );


        networkStatus.textContent =
            "PREDICTION COMPLETE";


        animateNetwork(
            result.prediction
        );

    }
    catch (error)
    {

        console.error(
            "Neural network error:",
            error
        );


        predictionElement.textContent =
            "?";


        confidenceElement.textContent =
            "Connection error";


        networkStatus.textContent =
            "NETWORK ERROR";


        networkStatus.classList.remove(
            "active"
        );

    }
}


// ============================================================
// START BUTTON
// ============================================================

startButton.addEventListener(
    "click",
    predictDigit
);


// ============================================================
// NETWORK VISUALIZATION
// ============================================================

const networkLayers =
    document.querySelectorAll(
        ".network-layer"
    );


const networkConnections =
    document.querySelectorAll(
        ".network-connections"
    );


const hiddenNeurons =
    document.querySelectorAll(
        ".neurons span"
    );


const outputNeurons =
    document.querySelectorAll(
        ".output-neurons span"
    );


// ============================================================
// RESET NETWORK
// ============================================================

function resetNetwork()
{

    networkLayers.forEach(
        (layer) =>
        {
            layer.classList.remove(
                "active"
            );
        }
    );


    networkConnections.forEach(
        (connection) =>
        {
            connection.classList.remove(
                "active"
            );
        }
    );


    hiddenNeurons.forEach(
        (neuron) =>
        {
            neuron.classList.remove(
                "active"
            );
        }
    );


    outputNeurons.forEach(
        (neuron) =>
        {
            neuron.classList.remove(
                "active"
            );
        }
    );
}


// ============================================================
// NETWORK ANIMATION
// ============================================================

function animateNetwork(
    prediction
)
{
    resetNetwork();


    networkStatus.textContent =
        "FORWARD PASS";


    networkStatus.classList.add(
        "active"
    );


    // --------------------------------------------------------
    // INPUT
    // --------------------------------------------------------

    setTimeout(
        () =>
        {

            networkLayers[0]
                .classList.add(
                    "active"
                );


            activateRandomNeurons(
                0,
                8
            );

        },
        100
    );


    // --------------------------------------------------------
    // INPUT → HIDDEN 1
    // --------------------------------------------------------

    setTimeout(
        () =>
        {

            networkConnections[0]
                .classList.add(
                    "active"
                );

        },
        450
    );


    // --------------------------------------------------------
    // HIDDEN 1
    // --------------------------------------------------------

    setTimeout(
        () =>
        {

            networkLayers[1]
                .classList.add(
                    "active"
                );


            activateRandomNeurons(
                8,
                7
            );

        },
        700
    );


    // --------------------------------------------------------
    // HIDDEN 1 → HIDDEN 2
    // --------------------------------------------------------

    setTimeout(
        () =>
        {

            networkConnections[1]
                .classList.add(
                    "active"
                );

        },
        1050
    );


    // --------------------------------------------------------
    // HIDDEN 2
    // --------------------------------------------------------

    setTimeout(
        () =>
        {

            networkLayers[2]
                .classList.add(
                    "active"
                );


            activateRandomNeurons(
                15,
                7
            );

        },
        1300
    );


    // --------------------------------------------------------
    // HIDDEN 2 → OUTPUT
    // --------------------------------------------------------

    setTimeout(
        () =>
        {

            networkConnections[2]
                .classList.add(
                    "active"
                );

        },
        1650
    );


    // --------------------------------------------------------
    // OUTPUT
    // --------------------------------------------------------

    setTimeout(
        () =>
        {

            networkLayers[3]
                .classList.add(
                    "active"
                );


            const output =
                outputNeurons[
                    prediction
                ];


            if (output)
            {
                output.classList.add(
                    "active"
                );
            }


            networkStatus.textContent =
                "PREDICTION: "
                + prediction;

        },
        1900
    );
}


// ============================================================
// ACTIVATE RANDOM NEURONS
// ============================================================

function activateRandomNeurons(
    startIndex,
    count
)
{
    for (
        let i = 0;
        i < count;
        i++
    )
    {

        const index =
            startIndex + i;


        if (
            hiddenNeurons[index]
        )
        {

            hiddenNeurons[index]
                .classList.add(
                    "active"
                );
        }
    }
}


// ============================================================
// FEEDBACK EFFECT
// ============================================================

function showFeedback(
    type
)
{

    feedbackOverlay.classList.remove(
        "success",
        "error"
    );


    void feedbackOverlay.offsetWidth;


    feedbackOverlay.classList.add(
        type
    );
}


// ============================================================
// YES BUTTON
// ============================================================

yesButton.addEventListener(
    "click",
    () =>
    {
        showFeedback(
            "success"
        );
    }
);


// ============================================================
// NO BUTTON
// ============================================================

noButton.addEventListener(
    "click",
    () =>
    {
        showFeedback(
            "error"
        );
    }
);


// ============================================================
// INITIALIZATION
// ============================================================

resizeSpaceCanvas();

createStars();

initializeDrawingCanvas();


requestAnimationFrame(
    drawSpace
);