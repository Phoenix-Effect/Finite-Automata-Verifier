var nodes = [
	{id: 1, label: '1', color: {background:'#FF7F32', border:'green'}},
	{id: 2, label: '2', color: '#5C6670'},
	{id: 5326, label: 'Dead-State', color: '#5C6670'},
	{id: 7, label: '7', color: '#5C6670'},
	{id: 3, label: '3', color: '#5C6670'},
	{id: 8, label: '8', color: '#5C6670'},
	{id: 4, label: '4', color: '#5C6670'},
	{id: 6, label: '6', color: '#5C6670'},
	{id: 5, label: '5', color: '#5C6670'}
];

var edges = [
	{from: 1, to:2, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 1, to:5326, arrows:'to', label: 'b, c, d, e, f', font: {align: 'top'}},
	{from: 1, to:7, arrows:'to', label: 'g', font: {align: 'top'}},
	{from: 2, to:5326, arrows:'to', label: 'a, d, e, f, g', font: {align: 'top'}},
	{from: 2, to:1, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 2, to:3, arrows:'to', label: 'c', font: {align: 'top'}},
	{from: 5326, to:5326, arrows:'to', label: 'a, b, c, d, e, f, g', font: {align: 'top'}},
	{from: 7, to:5326, arrows:'to', label: 'a, b, d, e, f, g', font: {align: 'top'}},
	{from: 7, to:8, arrows:'to', label: 'c', font: {align: 'top'}},
	{from: 3, to:5326, arrows:'to', label: 'a, c, e, f, g', font: {align: 'top'}},
	{from: 3, to:1, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 3, to:4, arrows:'to', label: 'd', font: {align: 'top'}},
	{from: 8, to:5326, arrows:'to', label: 'a, c, e, f, g', font: {align: 'top'}},
	{from: 8, to:1, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 8, to:4, arrows:'to', label: 'd', font: {align: 'top'}},
	{from: 4, to:5326, arrows:'to', label: 'a, b, c, d, f, g', font: {align: 'top'}},
	{from: 4, to:6, arrows:'to', label: 'e', font: {align: 'top'}},
	{from: 6, to:5326, arrows:'to', label: 'a, b, c, d, e, g', font: {align: 'top'}},
	{from: 6, to:5, arrows:'to', label: 'f', font: {align: 'top'}},
	{from: 5, to:5326, arrows:'to', label: 'a, c, d, e, f, g', font: {align: 'top'}},
	{from: 5, to:1, arrows:'to', label: 'b', font: {align: 'top'}}
];