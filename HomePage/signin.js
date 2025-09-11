const form = document.querySelector("form");

form.addEventListener("submit", function (event) {
  event.preventDefault();

  const email = document.querySelector("input[type='email']").value.trim();
  const password = document.querySelector("input[type='password']").value.trim();

  if (!email || !password) {
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

  // Simulate success
  alert("Sign in successful!");
  window.location.href = "../front.html"; // redirect after success
});