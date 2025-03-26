function sendGetRequest(action) {
    fetch(`/${action}`)
      .then((response) => response.text())
      .then((data) => {
        document.getElementById("response").innerText = data;
      })
      .catch((error) => {
        document.getElementById("response").innerText =
          "Erro ao enviar requisição.";
      });
  }