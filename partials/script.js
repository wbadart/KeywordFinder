$(document).ready(function(){

    var rows = CSV.map(function(row){
        return [new Date(row[0]), row[1], row[2], row[3]];
    }).map(function(cols){
        var tr = $('<tr/>');
        cols.forEach(function(col){
            tr.append($('<td/>', {text: col.toString()}));
        });
        return tr;
    }).forEach(function(tr){$('tbody').append(tr)});

    var chart = new Highcharts.Chart({
        chart: {
            renderTo: 'chart',
            type: 'scatter',
            options3d: {
                enabled: true,
                alpha: 10,
                beta: 30,
                depth: 250,
                viewDistance: 5,
                fitToPlot: false,
                frame: {
                    bottom: { size: 1, color: 'rgba(0,0,0,0.02)' },
                    back: { size: 1, color: 'rgba(0,0,0,0.04)' },
                    side: { size: 1, color: 'rgba(0,0,0,0.06)' }
                }
            },
        },
        title: {
            text: 'Data'
        },
        subtitle: {
            text: 'Click and drag the plot area to rotate in space'
        },
        plotOptions: {
            scatter: {
                width: 10,
                height: 10,
                depth: 10
            }
        },
        yAxis: {
            min: 0,
            max: 10,
            // title: null
        },
        xAxis: {
            labels: CSV.map(function(row){
                    return row[1]})
                .filter(function(row, i, rs){
                    i === rs.indexOf(row)})
            min: 0,
            max: 10,
            gridLineWidth: 1
        },
        zAxis: {
            min: 0,
            max: 10,
            // showFirstLabel: false
        },
        legend: {
            enabled: false
        },
        series: [{
            name: 'Reading',
            // colorByPoint: true,
            data: CSV.map(function(row){return row.slice(1)}),
        }]
    })
});

