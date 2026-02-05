import React from 'react';
import { Outlet } from 'react-router-dom';

import { DisplayExtendedMenuStore } from '../../store';
import NavigationBar from '../NavigationBar/NavigationBar';
import Menu from '../Menu/Menu';


import styles from './App.module.css';

import { fetchOptionsGET, fetchOptionsPOST} from '../fetchOptions';

function test() {
	const exampleData = {
		"username" : "Random User Name",
		"password": "Totally Real Password",
		"more data" : {
			"one" : "1",
			"five" : "5",
		},
		"more data after the more data" : "data again",
	};
	fetch("http://localhost:3490", {...fetchOptionsPOST,
		headers: {
			"Content-Type": "application/json",
		},
		body: JSON.stringify(exampleData),
	})
	.then((response) => {
		return response.text();
	})
	.then((data) => {
		console.log("Data Recieved: " + data);
	})
	.catch((error) => {
		console.error(error);
	});
}

function App() {
    const displayExtendedMenu = DisplayExtendedMenuStore((state) => state.value);

	test();

	return (
    	<div className={styles.appMain + " " + (displayExtendedMenu.data ? styles.displayExtendedMenu : styles.normal)}>
			<div className={styles.navigationBar}>
				<NavigationBar/>
			</div>
			<div className={styles.menu}>
				<Menu/>
			</div>
			<div className={styles.mainContent}>
				<Outlet/>
			</div>
    	</div>
  	);
}

export default App;
