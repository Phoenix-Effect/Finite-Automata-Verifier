var nodes = [
	{id: 1, label: '1', color: {background:'#FF7F32', border:'green'}},
	{id: 5326, label: 'Dead-State', color: '#5C6670'},
	{id: 12, label: '12', color: {background:'#78BE20', border:'green'}},
	{id: 2, label: '2', color: {background:'#78BE20', border:'green'}},
	{id: 123, label: '123', color: {background:'#78BE20', border:'green'}},
	{id: 3, label: '3', color: '#5C6670'},
	{id: 23, label: '23', color: {background:'#78BE20', border:'green'}}
];

var edges = [
	{from: 1, to:5326, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 1, to:12, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 5326, to:5326, arrows:'to', label: 'a, b', font: {align: 'top'}},
	{from: 12, to:2, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 12, to:123, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 2, to:2, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 2, to:3, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 123, to:23, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 123, to:123, arrows:'to', label: 'b', font: {align: 'top'}},
	{from: 3, to:3, arrows:'to', label: 'a, b', font: {align: 'top'}},
	{from: 23, to:23, arrows:'to', label: 'a', font: {align: 'top'}},
	{from: 23, to:3, arrows:'to', label: 'b', font: {align: 'top'}}
];