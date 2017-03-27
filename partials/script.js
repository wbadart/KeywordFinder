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

    var chart = Highcharts.chart('chart', {
        chart: { type: 'bar' },
        title: { text: 'Scan Results' },

        // Search terms along x-axis
        xAxis: {
            categories: ['Apples', 'Oranges', 'Pears', 'Grapes', 'Bananas']
        },

        // Total hits along y-axis
        yAxis: {
            min: 0,
            title: {
                text: 'Total fruit consumption'
            }
        },
        legend: { reversed: true },
        plotOptions: {
            series: { stacking: 'normal' }
        },

        // One series per website
        series: [{
            name: 'John',
            data: [5, 3, 4, 7, 2]
        }, {
            name: 'Jane',
            data: [2, 2, 3, 2, 1]
        }, {
            name: 'Joe',
            data: [3, 4, 4, 2, 5]
        }]

    });

});

