
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

        animateNetwork(result);

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
     document.querySelectorAll(".network-layer");

 const networkConnections =
     document.querySelectorAll(".network-connections");

 const outputNeurons =
     document.querySelectorAll(".output-neurons span");

 let networkAnimationTimers = [];


 // ============================================================
 // NETWORK DISPLAY MODES
 // ============================================================

 const networkSection =
     document.querySelector(".network-section");

 const networkCanvas =
     document.getElementById("networkCanvas");

 const networkCanvasContext =
     networkCanvas
         ? networkCanvas.getContext("2d")
         : null;

 const networkModeButtons =
     document.querySelectorAll("[data-network-mode]");

     let latestNetworkResult = null;

     let fullNetworkStage = -1;

function drawFullNetwork()
{
    if (!networkCanvas || !networkCanvasContext)
    {
        return;
    }

    const ctx = networkCanvasContext;
    const width = networkCanvas.width;
    const height = networkCanvas.height;

    ctx.clearRect(0, 0, width, height);

    ctx.fillStyle = "#050508";
    ctx.fillRect(0, 0, width, height);

    // Background grid.
    ctx.strokeStyle = "rgba(255, 55, 65, 0.045)";
    ctx.lineWidth = 1;

    for (let x = 40; x < width; x += 40)
    {
        ctx.beginPath();
        ctx.moveTo(x, 0);
        ctx.lineTo(x, height);
        ctx.stroke();
    }

    for (let y = 40; y < height; y += 40)
    {
        ctx.beginPath();
        ctx.moveTo(0, y);
        ctx.lineTo(width, y);
        ctx.stroke();
    }

    const labels = [
        { name: "INPUT", size: "784 PIXELS", x: 105 },
        { name: "HIDDEN 1", size: "128 NEURONS", x: 365 },
        { name: "HIDDEN 2", size: "64 NEURONS", x: 685 },
        { name: "OUTPUT", size: "10 CLASSES", x: 1035 }
    ];

    ctx.textAlign = "center";
    ctx.textBaseline = "middle";

    labels.forEach(layer =>
    {
        ctx.font = "bold 15px monospace";
        ctx.fillStyle = "#ff4655";
        ctx.fillText(layer.name, layer.x, 30);

        ctx.font = "11px monospace";
        ctx.fillStyle = "#92929e";
        ctx.fillText(layer.size, layer.x, 49);
    });

    // Draw all 784 input pixels as a real 28x28 grid.
    const pixelSize = 4;
    const pixelGap = 1;
    const inputSize = 28 * (pixelSize + pixelGap) - pixelGap;
    const inputX = 105 - inputSize / 2;
    const inputY = 110;

    for (let i = 0; i < 784; i++)
    {
        const row = Math.floor(i / 28);
        const col = i % 28;

        ctx.fillStyle = "#24242b";
        ctx.fillRect(
            inputX + col * (pixelSize + pixelGap),
            inputY + row * (pixelSize + pixelGap),
            pixelSize,
            pixelSize
        );
    }

    // Draw every neuron in the two hidden layers.
    function drawNeuronGrid(count, columns, centerX, topY, cellSize)
    {
        const rows = Math.ceil(count / columns);
        const gap = 3;
        const totalWidth = columns * cellSize + (columns - 1) * gap;
        const startX = centerX - totalWidth / 2;

        for (let i = 0; i < count; i++)
        {
            const row = Math.floor(i / columns);
            const col = i % columns;

            ctx.fillStyle = "#24242b";
            ctx.fillRect(
                startX + col * (cellSize + gap),
                topY + row * (cellSize + gap),
                cellSize,
                cellSize
            );
        }
    }

    drawNeuronGrid(128, 16, 365, 115, 7);
    drawNeuronGrid(64, 8, 685, 145, 11);

    // Output layer: one bar for each digit from 0 to 9.
    for (let digit = 0; digit < 10; digit++)
    {
        const y = 90 + digit * 32;

        ctx.fillStyle = "#24242b";
        ctx.fillRect(990, y, 90, 18);

        ctx.font = "12px monospace";
        ctx.textAlign = "right";
        ctx.fillStyle = "#92929e";
        ctx.fillText(String(digit), 980, y + 9);
    }

    ctx.textAlign = "center";
    ctx.font = "11px monospace";
    ctx.fillStyle = "#666672";
    ctx.fillText(
        "WAITING FOR PREDICTION",
        width / 2,
        455
    );
}

 // ============================================================
 // NETWORK DISPLAY MODES
 // ============================================================

networkModeButtons.forEach(button =>
{
    button.addEventListener("click", () =>
    {
        const mode = button.dataset.networkMode;

        if (
            !networkSection ||
            !["full", "compact"].includes(mode)
        )
        {
            return;
        }

        networkSection.classList.toggle(
            "mode-full",
            mode === "full"
        );

        networkSection.classList.toggle(
            "mode-compact",
            mode === "compact"
        );

        networkModeButtons.forEach(modeButton =>
        {
            const isActive =
                modeButton.dataset.networkMode === mode;

            modeButton.classList.toggle("active", isActive);

            modeButton.setAttribute(
                "aria-pressed",
                String(isActive)
            );
        });

        if (mode === "full")
        {
            drawFullNetworkTrace(
                latestNetworkResult,
                fullNetworkStage
            );
        }
    });
});


 // ============================================================
 // SCHEDULE ANIMATION STEP
 // ============================================================

 // ============================================================
 // RENDER REAL NETWORK ACTIVATIONS
 // ============================================================

 
function drawFullNetworkTrace(result, stage)
{
    drawFullNetwork();

    if (!result || !networkCanvasContext)
    {
        return;
    }

    const ctx = networkCanvasContext;

    const layers = [
        {
            name: "INPUT",
            values: result.input,
            stage: 0,
            centerX: 105,
            topY: 110,
            columns: 28,
            cellSize: 4,
            gap: 1
        },
        {
            name: "HIDDEN 1",
            values: result.hidden1,
            stage: 2,
            centerX: 365,
            topY: 115,
            columns: 16,
            cellSize: 7,
            gap: 3
        },
        {
            name: "HIDDEN 2",
            values: result.hidden2,
            stage: 4,
            centerX: 685,
            topY: 145,
            columns: 8,
            cellSize: 11,
            gap: 3
        }
    ];

    // Render the actual activation value of every neuron.
    layers.forEach(layer =>
    {
        if (
            stage < layer.stage ||
            !Array.isArray(layer.values)
        )
        {
            return;
        }

        const values = layer.values;
        const maxValue = Math.max(
            0.000001,
            ...values.map(value =>
                Math.abs(Number(value) || 0)
            )
        );

        const totalWidth =
            layer.columns * (layer.cellSize + layer.gap)
            - layer.gap;

        const startX = layer.centerX - totalWidth / 2;

        values.forEach((rawValue, index) =>
        {
            const value = Number(rawValue) || 0;
            const strength = Math.min(
                1,
                Math.abs(value) / maxValue
            );

            const row = Math.floor(index / layer.columns);
            const col = index % layer.columns;

            const x = startX +
                col * (layer.cellSize + layer.gap);

            const y = layer.topY +
                row * (layer.cellSize + layer.gap);

            ctx.fillStyle =
                `rgba(255, ${Math.round(80 + strength * 100)}, ` +
                `${Math.round(90 + strength * 100)}, ` +
                `${0.2 + strength * 0.8})`;

            ctx.fillRect(
                x,
                y,
                layer.cellSize,
                layer.cellSize
            );
        });
    });

    // Output probabilities are returned by the backend.
    if (
        stage >= 6 &&
        Array.isArray(result.output)
    )
    {
        result.output.forEach((rawValue, digit) =>
        {
            const probability = Math.max(
                0,
                Number(rawValue) || 0
            );

            const y = 90 + digit * 32;

            ctx.fillStyle = "rgba(255, 38, 56, 0.15)";
            ctx.fillRect(990, y, 90, 18);

            ctx.fillStyle = "#ff4655";
            ctx.fillRect(
                990,
                y,
                90 * Math.min(1, probability),
                18
            );

            ctx.textAlign = "left";
            ctx.font = "11px monospace";
            ctx.fillStyle = "#f4dadd";
            ctx.fillText(
                `${(probability * 100).toFixed(1)}%`,
                1090,
                y + 9
            );
        });
    }

    const stageLabels = [
        "INPUT PIXELS",
        "INPUT → HIDDEN 1",
        "HIDDEN 1 ACTIVATIONS",
        "HIDDEN 1 → HIDDEN 2",
        "HIDDEN 2 ACTIVATIONS",
        "HIDDEN 2 → OUTPUT",
        "OUTPUT PROBABILITIES"
    ];

    ctx.textAlign = "center";
    ctx.font = "bold 12px monospace";
    ctx.fillStyle = "#ff6875";
    ctx.fillText(
        stageLabels[stage] || "NETWORK READY",
        networkCanvas.width / 2,
        435
    );
}

 function scheduleNetworkStep(callback, delay)
 {
     const timer = setTimeout(callback, delay);

     networkAnimationTimers.push(timer);
 }

 // ============================================================
 // SAMPLE ARRAY
 // ============================================================

 function sampleArray(values, count)
 {
     if (
         !Array.isArray(values) ||
         values.length === 0 ||
         count <= 0
     )
     {
         return [];
     }

     if (values.length <= count)
     {
         return values.slice();
     }

     const sampled = [];

     for (let i = 0; i < count; i++)
     {
         const index = Math.round(
             i * (values.length - 1) /
             Math.max(1, count - 1)
         );

         sampled.push(values[index]);
     }

     return sampled;
 }

 // ============================================================
 // NORMALIZE ACTIVATIONS
 // ============================================================

 function normalizeActivations(values)
 {
     const maxValue = Math.max(
         0.000001,
         ...values.map(
             value => Math.abs(Number(value) || 0)
         )
     );

     return values.map(value =>
     {
         return Math.min(
             1,
             Math.abs(Number(value) || 0) / maxValue
         );
     });
 }

 // ============================================================
 // RENDER NEURON VALUES
 // ============================================================

 function renderNeuronValues(container, values, label)
 {
     if (!container || !Array.isArray(values))
     {
         return;
     }

     const neurons =
         container.querySelectorAll(".neurons span");

     const displayedValues =
         sampleArray(values, neurons.length);

     const strengths =
         normalizeActivations(displayedValues);

     neurons.forEach((neuron, index) =>
     {
         const value =
             Number(displayedValues[index]) || 0;

         const strength =
             strengths[index] || 0;

         neuron.classList.toggle(
             "active",
             strength > 0.01
         );

         neuron.style.opacity =
             String(0.25 + strength * 0.75);

         neuron.style.boxShadow =
             strength > 0.01
                 ? `0 0 ${4 + strength * 16}px rgba(255, 55, 65, ${0.15 + strength * 0.65})`
                 : "none";

         neuron.title =
             `${label}: ${value.toFixed(6)}`;

         neuron.dataset.activation =
             String(value);
     });
 }

 // ============================================================
 // RESET NETWORK
 // ============================================================

 function resetNetwork()
 {
     networkAnimationTimers.forEach(clearTimeout);

     networkAnimationTimers = [];

     networkLayers.forEach(layer =>
     {
         layer.classList.remove("active");

         layer.querySelectorAll(".neurons span")
             .forEach(neuron =>
             {
                 neuron.classList.remove("active");

                 neuron.style.opacity = "";
                 neuron.style.boxShadow = "";

                 neuron.removeAttribute("title");

                 delete neuron.dataset.activation;
             });
     });

     networkConnections.forEach(connection =>
     {
         connection.classList.remove("active");
     });

     outputNeurons.forEach(neuron =>
     {
         neuron.classList.remove("active");

         neuron.style.opacity = "";
         neuron.style.boxShadow = "";

         neuron.removeAttribute("title");

         delete neuron.dataset.probability;
     });
 }

 // ============================================================
 // NETWORK ANIMATION
 // ============================================================

 function animateNetwork(result)
 {
     resetNetwork();

     if (
         !result ||
         !Array.isArray(result.input) ||
         !Array.isArray(result.hidden1) ||
         !Array.isArray(result.hidden2) ||
         !Array.isArray(result.output)
     )
     {
         console.error(
             "Incomplete neural network trace:",
             result
         );

         networkStatus.textContent =
             "TRACE DATA MISSING";

         networkStatus.classList.remove("active");

         return;
     }

     latestNetworkResult = result;

     fullNetworkStage = -1;

     networkStatus.textContent =
         "FORWARD PASS";

     networkStatus.classList.add("active");


     // Animate the full canvas using real backend activations.
     const fullStages = [
        { stage: 0, delay: 100 },
        { stage: 1, delay: 450 },
        { stage: 2, delay: 700 },
        { stage: 3, delay: 1050 },
        { stage: 4, delay: 1300 },
        { stage: 5, delay: 1650 },
        { stage: 6, delay: 1900 }
     ];

     fullStages.forEach(({ stage, delay }) =>
     {
        scheduleNetworkStep(() =>
        {
             fullNetworkStage = stage;

             if (
                 networkSection &&
                 networkSection.classList.contains("mode-full")
            )
            {
                 drawFullNetworkTrace(
                     latestNetworkResult,
                    fullNetworkStage
                );
            }
        }, delay);
     });

     const inputLayer =
         networkLayers[0];

     const hidden1Layer =
         networkLayers[1];

     const hidden2Layer =
         networkLayers[2];

     const outputLayer =
         networkLayers[3];

     // --------------------------------------------------------
     // STAGE 1: INPUT
     // --------------------------------------------------------

     scheduleNetworkStep(() =>
     {
         if (inputLayer)
         {
             inputLayer.classList.add("active");

             renderNeuronValues(
                 inputLayer,
                 result.input,
                 "Input pixel"
             );
         }
     }, 100);

     // --------------------------------------------------------
     // STAGE 2: INPUT -> HIDDEN 1
     // --------------------------------------------------------

     scheduleNetworkStep(() =>
     {
         if (networkConnections[0])
         {
             networkConnections[0].classList.add("active");
         }
     }, 450);

     // --------------------------------------------------------
     // STAGE 3: HIDDEN LAYER 1
     // --------------------------------------------------------

     scheduleNetworkStep(() =>
     {
         if (hidden1Layer)
         {
             hidden1Layer.classList.add("active");

             renderNeuronValues(
                 hidden1Layer,
                 result.hidden1,
                 "Hidden layer 1 activation"
             );
         }
     }, 700);

     // --------------------------------------------------------
     // STAGE 4: HIDDEN 1 -> HIDDEN 2
     // --------------------------------------------------------

     scheduleNetworkStep(() =>
     {
         if (networkConnections[1])
         {
             networkConnections[1].classList.add("active");
         }
     }, 1050);

     // --------------------------------------------------------
     // STAGE 5: HIDDEN LAYER 2
     // --------------------------------------------------------

     scheduleNetworkStep(() =>
     {
         if (hidden2Layer)
         {
             hidden2Layer.classList.add("active");

             renderNeuronValues(
                 hidden2Layer,
                 result.hidden2,
                 "Hidden layer 2 activation"
             );
         }
     }, 1300);

     // --------------------------------------------------------
     // STAGE 6: HIDDEN 2 -> OUTPUT
     // --------------------------------------------------------

     scheduleNetworkStep(() =>
     {
         if (networkConnections[2])
         {
             networkConnections[2].classList.add("active");
         }
     }, 1650);

     // --------------------------------------------------------
     // STAGE 7: OUTPUT
     // --------------------------------------------------------

     scheduleNetworkStep(() =>
     {
         if (outputLayer)
         {
             outputLayer.classList.add("active");
         }

         const probabilities =
             result.output;

         const logits =
             Array.isArray(result.logits)
                 ? result.logits
                 : [];

         const maxProbability = Math.max(
             0.000001,
             ...probabilities.map(
                 value => Number(value) || 0
             )
         );

         outputNeurons.forEach((neuron, index) =>
         {
             const probability =
                 Number(probabilities[index]) || 0;

             const strength =
                 Math.min(
                     1,
                     probability / maxProbability
                 );

             const isPrediction =
                 index === Number(result.prediction);

             neuron.classList.toggle(
                 "active",
                 isPrediction
             );

             neuron.style.opacity =
                 String(0.3 + strength * 0.7);

             neuron.style.boxShadow =
                 probability > 0
                     ? `0 0 ${4 + strength * 18}px rgba(255, 55, 65, ${0.15 + strength * 0.65})`
                     : "none";

             neuron.dataset.probability =
                 String(probability);
             neuron.title =
                 `Digit ${index}: ${(probability * 100).toFixed(2)}% probability` +
                 (
                     logits[index] !== undefined
                         ? `; logit: ${Number(logits[index]).toFixed(6)}`
                         : ""
                 );
         });

         networkStatus.textContent =
             "PREDICTION: " + result.prediction;

     }, 1900);
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