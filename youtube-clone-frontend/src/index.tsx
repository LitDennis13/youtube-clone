import React from 'react';
import ReactDOM from 'react-dom/client';
import { createBrowserRouter, RouterProvider } from "react-router-dom";

import App from './components/App/App';
import HomePage from './components/HomePage/HomePage';
import SubscriptionsPage from './components/SubscriptionsPage/SubscriptionsPage';
import HistoryPage from './components/HistoryPage/HistoryPage';
import PlayListsPage from './components/PlayListsPage/PlayListsPage';
import MyVideosPage from './components/MyVideosPage/MyVideosPage';
import SignInSignUpPage from './components/SignInSignUpPage/SignInSignUpPage';
import PageNotFoundPage from './components/PageNotFoundPage/PageNotFoundPage';

import ErrorPage from './components/ErrorPage/ErrorPage';

import reportWebVitals from './reportWebVitals';

import './index.css';
import "./other/josh-comeau-css-reset.css";


const router = createBrowserRouter([
{
	path: "/",
    element: <App />,
    errorElement: <ErrorPage />,
    children: [
		{
			path: "/",
			element: <HomePage />,
		},
		{
			path: "/subscriptions",
			element: <SubscriptionsPage />,
		},
		{
			path: "/history",
			element: <HistoryPage />,
		},
		{
			path: "/playlists",
			element: <PlayListsPage />,
		},
		{
		path: "/my-videos",
		element: <MyVideosPage />,
		},
		{
		path: "/signin",
		element: <SignInSignUpPage />,
		},
		{
			path: "*",
			element: <PageNotFoundPage />,
		}
	]
}
]);

const root = ReactDOM.createRoot(
  document.getElementById('root') as HTMLElement
);
root.render(
  <React.StrictMode>
    <RouterProvider router={router} />
  </React.StrictMode>
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
