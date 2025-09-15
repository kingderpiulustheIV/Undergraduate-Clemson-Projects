<!-- 
Sean Farrell
7/12/2025
CPSC 3750 Wooster
ASSIGNMENT: Group Forms
DESCRIPTION: This PHP application shows demonstrates the processing of various form inputs including text, textarea, hidden fields, 
password, checkboxes, radio buttons, selection lists, file uploads, and URL inputs. 0t displays the submitted data in a structured format.

This is process_form.php file containing the processing logic for the form submission. It retrieves the data from the POST request, processes it, and displays the results in a user-friendly format.
-->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Form Submission Results</title>
    
    <!-- Internal CSS file for styling -->
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
        }
        h1 {
            text-align: center;
            color: #333;
        }
        .result-container {
            background-color: #f9f9f9;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
        }
        .result-item {
            margin-bottom: 15px;
            padding: 15px;
            background-color: #fff;
            border-radius: 5px;
            border-left: 4px solid #c43b19;
        }
        .result-label {
            font-weight: bold;
            margin-bottom: 5px;
            background-color: #c43b19;
            color: white;
            padding: 5px 10px;
            border-radius: 4px;
            display: inline-block;
        }
        .result-value {
            padding: 5px 0;
            word-break: break-all;
        }
        .back-button {
            display: block;
            text-align: center;
            margin-top: 20px;
            background-color: #c43b19;
            color: white;
            padding: 10px 15px;
            text-decoration: none;
            border-radius: 4px;
            width: 150px;
            margin: 20px auto;
        }
        .file-info {
            margin-top: 10px;
            font-style: italic;
        }
    </style>
</head>
<body>
    <h1>Form Submission Results</h1>
    
    <div class="result-container">
        <?php
        // Text Input
        if(isset($_POST['username'])) {
            echo "<div class='result-item'>";
            echo "<div class='result-label'>Text Input (Username)</div>";
            echo "<div class='result-value'>" . htmlspecialchars($_POST['username']) . "</div>";
            echo "</div>";
        }
        
        // Textarea
        if(isset($_POST['comments'])) {
            echo "<div class='result-item'>";
            echo "<div class='result-label'>Textarea (Comments)</div>";
            echo "<div class='result-value'>" . nl2br(htmlspecialchars($_POST['comments'])) . "</div>";
            echo "</div>";
        }
        
        // Hidden Data
        if(isset($_POST['hidden_id'])) {
            echo "<div class='result-item'>";
            echo "<div class='result-label'>Hidden Input</div>";
            echo "<div class='result-value'>Hidden ID: " . htmlspecialchars($_POST['hidden_id']) . "</div>";
            echo "</div>";
        }
        
        // Password
        if(isset($_POST['password'])) {
            echo "<div class='result-item'>";
            echo "<div class='result-label'>Password Input</div>";
            echo "<div class='result-value'>Password: " . str_repeat("*", strlen($_POST['password'])) . " (Length: " . strlen($_POST['password']) . ")</div>";
            echo "</div>";
        }
        
        // Array of Checkboxes
        if(isset($_POST['languages']) && is_array($_POST['languages'])) {
            echo "<div class='result-item'>";
            echo "<div class='result-label'>Checkbox Array (Languages)</div>";
            echo "<div class='result-value'>";
            if(count($_POST['languages']) > 0) {
                echo "<ul>";
                foreach($_POST['languages'] as $language) {
                    echo "<li>" . htmlspecialchars($language) . "</li>";
                }
                echo "</ul>";
            } else {
                echo "No languages selected";
            }
            echo "</div>";
            echo "</div>";
        } else {
            echo "<div class='result-item'>";
            echo "<div class='result-label'>Checkbox Array (Languages)</div>";
            echo "<div class='result-value'>No languages selected</div>";
            echo "</div>";
        }
        
        // Radio Buttons
        if(isset($_POST['favorite_pet'])) {
            echo "<div class='result-item'>";
            echo "<div class='result-label'>Radio Buttons (Favorite Pet)</div>";
            echo "<div class='result-value'>" . htmlspecialchars($_POST['favorite_pet']) . "</div>";
            echo "</div>";
        } else {
            echo "<div class='result-item'>";
            echo "<div class='result-label'>Radio Buttons (Favorite Pet)</div>";
            echo "<div class='result-value'>No pet selected</div>";
            echo "</div>";
        }
        
        // Selection List
        if(isset($_POST['country']) && !empty($_POST['country'])) {
            echo "<div class='result-item'>";
            echo "<div class='result-label'>Selection List (Country)</div>";
            echo "<div class='result-value'>" . htmlspecialchars($_POST['country']) . "</div>";
            echo "</div>";
        } else {
            echo "<div class='result-item'>";
            echo "<div class='result-label'>Selection List (Country)</div>";
            echo "<div class='result-value'>No country selected</div>";
            echo "</div>";
        }
        
        // File Upload
        echo "<div class='result-item'>";
        echo "<div class='result-label'>File Upload (Profile Picture)</div>";
        if(isset($_FILES['profile_pic']) && $_FILES['profile_pic']['error'] == 0) {
            echo "<div class='result-value'>";
            echo "File uploaded successfully!";
            echo "<div class='file-info'>";
            echo "Filename: " . htmlspecialchars($_FILES['profile_pic']['name']) . "<br>";
            echo "File Type: " . htmlspecialchars($_FILES['profile_pic']['type']) . "<br>";
            echo "File Size: " . (($_FILES['profile_pic']['size'] / 1024) < 1024 ? 
                              round($_FILES['profile_pic']['size'] / 1024, 2) . " KB" : 
                              round($_FILES['profile_pic']['size'] / (1024 * 1024), 2) . " MB");
            echo "</div>";
            echo "</div>";
        } else {
            echo "<div class='result-value'>No file uploaded or an error occurred</div>";
            if (isset($_FILES['profile_pic']) && $_FILES['profile_pic']['error'] > 0) {
                $errors = array(
                    1 => "The uploaded file exceeds the upload_max_filesize directive in php.ini",
                    2 => "The uploaded file exceeds the MAX_FILE_SIZE directive that was specified in the HTML form",
                    3 => "The uploaded file was only partially uploaded",
                    4 => "No file was uploaded",
                    6 => "Missing a temporary folder",
                    7 => "Failed to write file to disk",
                    8 => "A PHP extension stopped the file upload"
                );
                echo "<div class='file-info'>Error: " . ($errors[$_FILES['profile_pic']['error']] ?? "Unknown error") . "</div>";
            }
        }
        echo "</div>";
        
        // URL Input
        if(isset($_POST['website']) && !empty($_POST['website'])) {
            echo "<div class='result-item'>";
            echo "<div class='result-label'>URL Input (Website)</div>";
            echo "<div class='result-value'>";
            echo htmlspecialchars($_POST['website']) . "<br>";
            echo "<a href='" . htmlspecialchars($_POST['website']) . "' target='_blank'>Visit website</a>";
            echo "</div>";
            echo "</div>";
        } else {
            echo "<div class='result-item'>";
            echo "<div class='result-label'>URL Input (Website)</div>";
            echo "<div class='result-value'>No website URL provided</div>";
            echo "</div>";
        }
        ?>
    </div>
    
    <a href="groupforms.html" class="back-button">Back to Form</a>
</body>
</html>