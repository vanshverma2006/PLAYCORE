const signupForm = document.querySelector("form");

signupForm.addEventListener("submit", function (event) {
  event.preventDefault();

  const name = document.querySelector("input[type='text']").value.trim();
  const email = document.querySelector("input[type='email']").value.trim();
  const password = document.querySelectorAll("input[type='password']")[0].value.trim();
  const confirmPassword = document.querySelectorAll("input[type='password']")[1].value.trim();

  if (!name || !email || !password || !confirmPassword) {
    alert("Please fill in all fields.");
    return;
  }

  const emailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  if (!emailPattern.test(email)) {
    alert("Please enter a valid email address.");
    return;
  }

  if (password.length < 6) {
    alert("Password must be at least 6 characters long.");
    return;
  }

  if (password !== confirmPassword) {
    alert("Passwords do not match.");
    return;
  }

  alert("Sign up successful!");
  window.location.href = "signin.html"; 
});