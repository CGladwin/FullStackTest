const express = require("express");
const fileUpload = require("express-fileupload");
const { exec } = require("child_process");
const path = require("path");
const fs = require("fs");

const app = express();
const PORT = 3000;

// Middleware to handle file uploads
app.use(fileUpload());

// Serve static files from the "public" directory
app.use(express.static(path.join(__dirname, "public")));

// Route to handle file upload and conversion
app.post("/upload", (req, res) => {
    if (!req.files || !req.files.ppmFile) {
        return res.status(400).send("No file uploaded.");
    }

    const ppmFile = req.files.ppmFile;
    const uploadPath = path.join(__dirname, "uploads", ppmFile.name);
    const outputPath = path.join(__dirname, "uploads", "output.png");

    // Save the uploaded file
    ppmFile.mv(uploadPath, (err) => {
        if (err) {
            return res.status(500).send(err);
        }

        // Call the C++ program to convert PPM to PNG
        exec(`./cpp/ppm2png ${uploadPath} ${outputPath}`, (error, stdout, stderr) => {
            if (error) {
                console.error(`Error: ${stderr}`);
                return res.status(500).send("Conversion failed.");
            }

            // Send the converted PNG file back to the client
            res.download(outputPath, "converted.png", (err) => {
                if (err) {
                    console.error("Error sending file:", err);
                }

                // Clean up files
                fs.unlinkSync(uploadPath);
                fs.unlinkSync(outputPath);
            });
        });
    });
});

// Serve the frontend at the root path
app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname, "public", "index.html"));
});

app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});