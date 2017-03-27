$(document).ready(function(){

    // Create <table>
    var rows = CSV.map(function(row){
        return [new Date(row[0]), row[1], row[2], row[3]];
    }).map(function(cols){
        var tr = $('<tr/>');
        cols.forEach(function(col){
            tr.append($('<td/>', {text: col.toString()}));
        });
        return tr;
    }).forEach(function(tr){$('tbody').append(tr)});

    // Turn CSV into a nicer data structure, organized by term
    var data = CSV.reduce(function(acc, row){
        if(!acc[row[1]]) acc[row[1]] = {}
        acc[row[1]][row[2]] = row[3];
        return acc;
    }, {});

    var chart = Highcharts.chart('chart', {
        chart: { type: 'bar' },
        title: { text: 'Scan Results' },

        // Search terms along x-axis
        xAxis: {
            // categories: ['Apples', 'Oranges', 'Pears', 'Grapes', 'Bananas']
            categories: Object.keys(data)
        },

        // Total hits along y-axis
        yAxis: {
            min: 0,
            title: {
                text: 'Total hits'
            }
        },
        legend: { reversed: true },
        plotOptions: {
            series: { stacking: 'normal' }
        },

        // One series per website
        series: mkseries(data, Object.keys(data))
    });

});

function mkseries(data, terms){
    var sites = Object.keys(data[Object.keys(data)[0]]);
    return sites.map(function(site){
        return { name: site
               , data: terms.map(function(t){ return data[t][site] })
               }
    });
}

