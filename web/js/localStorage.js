function setCredentials()
{
    event.preventDefault(); 
    
    const email = document.getElementById('email').value;
    
    // 2. Store the data
    localStorage.setItem('email', email);
    
    console.log("Email stored:", email);
    
    // 3. Redirect to the map
    window.location.href = 'map.php';
    
    // Return false to ensure no other code runs
    return false;
}

function checkCredentials()
{
    const email = window.localStorage.getItem("email");
    const element = document.getElementById("emailShow");
    element.textContent = email;
}

function logout()
{
   localStorage.removeItem('email'); 
    
    console.log("User logged out, storage cleared.");
    
    // Now actually send them back to the login page
    window.location.href = 'login.php';
}

window.onload = checkCredentials;