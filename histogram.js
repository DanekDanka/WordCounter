
function drawHistogram(canvas, data, options) {
    if (!canvas.getContext) {
        return;
    }
    var ctx = canvas.getContext('2d');
    var width = canvas.width;
    var height = canvas.height;
    var barWidth = width / data.length;

    ctx.clearRect(0, 0, width, height);
    ctx.fillStyle = options.color || 'black';

    for (var i = 0; i < data.length; i++) {
        var barHeight = (data[i] / Math.max(...data)) * height;
        ctx.fillRect(i * barWidth, height - barHeight, barWidth - 1, barHeight);
    }
}