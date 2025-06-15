<script>
  const fwdBtn = document.getElementById('foward');
  const bckBtn = document.getElementById('backward');
  const rgtBtn = document.getElementById('right');
  const lftBtn = document.getElementById('left');
  const count = document.getElementById('count');

  let fwdInterval = null;
  let bckInterval = null;
  let rgtInterval = null;
  let lftInterval = null;

  function startSendingRequest(url, updateCount) {
    fetch(url).then(r => r.text()).then(v => {
      updateCount(v);
    });
    return setInterval(() => {
      fetch(url).then(r => r.text()).then(v => {
        updateCount(v);
      });
    }, 200);
  }

  function stopSendingRequest(intervalId) {
    if (intervalId !== null) {
      clearInterval(intervalId);
    }
  }

  function updateCountValue(v) {
    count.dataset.count = v;
    count.innerText = v;
  }

  // Forward button
  fwdBtn.addEventListener('mousedown', () => {
    fwdInterval = startSendingRequest('/foward', updateCountValue);
  });
  fwdBtn.addEventListener('touchstart', () => {
    fwdInterval = startSendingRequest('/foward', updateCountValue);
  });
  fwdBtn.addEventListener('mouseup', () => {
    stopSendingRequest(fwdInterval);
    fwdInterval = null;
  });
  fwdBtn.addEventListener('mouseleave', () => {
    stopSendingRequest(fwdInterval);
    fwdInterval = null;
  });
  fwdBtn.addEventListener('touchend', () => {
    stopSendingRequest(fwdInterval);
    fwdInterval = null;
  });
  fwdBtn.addEventListener('touchcancel', () => {
    stopSendingRequest(fwdInterval);
    fwdInterval = null;
  });

  // Backward button
  bckBtn.addEventListener('mousedown', () => {
    bckInterval = startSendingRequest('/backward', updateCountValue);
  });
  bckBtn.addEventListener('touchstart', () => {
    bckInterval = startSendingRequest('/backward', updateCountValue);
  });
  bckBtn.addEventListener('mouseup', () => {
    stopSendingRequest(bckInterval);
    bckInterval = null;
  });
  bckBtn.addEventListener('mouseleave', () => {
    stopSendingRequest(bckInterval);
    bckInterval = null;
  });
  bckBtn.addEventListener('touchend', () => {
    stopSendingRequest(bckInterval);
    bckInterval = null;
  });
  bckBtn.addEventListener('touchcancel', () => {
    stopSendingRequest(bckInterval);
    bckInterval = null;
  });

  // Right button
  rgtBtn.addEventListener('mousedown', () => {
    rgtInterval = startSendingRequest('/right', updateCountValue);
  });
  rgtBtn.addEventListener('touchstart', () => {
    rgtInterval = startSendingRequest('/right', updateCountValue);
  });
  rgtBtn.addEventListener('mouseup', () => {
    stopSendingRequest(rgtInterval);
    rgtInterval = null;
  });
  rgtBtn.addEventListener('mouseleave', () => {
    stopSendingRequest(rgtInterval);
    rgtInterval = null;
  });
  rgtBtn.addEventListener('touchend', () => {
    stopSendingRequest(rgtInterval);
    rgtInterval = null;
  });
  rgtBtn.addEventListener('touchcancel', () => {
    stopSendingRequest(rgtInterval);
    rgtInterval = null;
  });

  // Left button
  lftBtn.addEventListener('mousedown', () => {
    lftInterval = startSendingRequest('/left', updateCountValue);
  });
  lftBtn.addEventListener('touchstart', () => {
    lftInterval = startSendingRequest('/left', updateCountValue);
  });
  lftBtn.addEventListener('mouseup', () => {
    stopSendingRequest(lftInterval);
    lftInterval = null;
  });
  lftBtn.addEventListener('mouseleave', () => {
    stopSendingRequest(lftInterval);
    lftInterval = null;
  });
  lftBtn.addEventListener('touchend', () => {
    stopSendingRequest(lftInterval);
    lftInterval = null;
  });
  lftBtn.addEventListener('touchcancel', () => {
    stopSendingRequest(lftInterval);
    lftInterval = null;
  });
</script>
