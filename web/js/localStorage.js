function setCredentials()
{
    const email = document.getElementById('email').value;
    
    localStorage.setItem('email', email);
    
    console.log("Email stored:", email);
    window.location.href = 'map.php';
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
    localStorage.removeItem('userEmail');
    
    console.log("User logged out, storage cleared.");
}

window.onload = checkCredentials;