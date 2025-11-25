import { useState, useEffect } from "react";
import { Link } from "react-router-dom";

import { PageOptions } from "../../types";
import { DisplayExtendedMenuStore, SelectedPageStore } from "../../store";

import styles from "./MenuStyles.module.css";

import homeIcon from "../../images/home.svg";
import subscriptionsIcon from "../../images/subscriptions.svg";
import historyIcon from "../../images/history.svg";
import playlistsIcon from "../../images/playlists.svg";
import videosIcon from "../../images/videos.svg";

function Menu() {
    const displayExtendedMenu = DisplayExtendedMenuStore((state) => state.value);
    const selectedPage = SelectedPageStore((state) => state.value);

    return (
        displayExtendedMenu.data ? 
        <div className={styles.menuExtended}>
            <Link to={"/"}>
                <button id={selectedPage.page == PageOptions.Home ? styles.selected : ""} className={styles.homeButton}>
                    <img src={homeIcon} alt="home icon" />Home
                </button>
            </Link>

            <Link to={"/subscriptions"}>
                <button id={selectedPage.page == PageOptions.Subscription ? styles.selected : ""} className={styles.subscriptionsButton}>
                    <img src={subscriptionsIcon} alt="subscriptions icon" />Subscriptions
                </button>
            </Link>

            <Link to={"/history"}>
                <button id={selectedPage.page == PageOptions.History ? styles.selected : ""} className={styles.historyButton}>
                    <img src={historyIcon} alt="history icon" />History
                </button>
            </Link>

            <Link to={"/playlists"}>
                <button id={selectedPage.page == PageOptions.Playlists ? styles.selected : ""} className={styles.playListsButton}>
                    <img src={playlistsIcon} alt="playlists icon" />Playlists
                </button>
            </Link>

            <Link to={"/my-videos"}>
                <button id={selectedPage.page == PageOptions.MyVideos ? styles.selected : ""} className={styles.myVideosButton}>
                    <img src={videosIcon} alt="my videos icon" />My Videos
                </button>
            </Link>
        </div>
        :
        <div className={styles.menuNormal}>
            <Link to={"/"}>
                <button id={selectedPage.page == PageOptions.Home ? styles.selected : ""} className={styles.homeButton}>
                    <img src={homeIcon} alt="home icon" />Home
                </button>
            </Link>

            <Link to={"/subscriptions"}>
                <button id={selectedPage.page == PageOptions.Subscription ? styles.selected : ""} className={styles.subscriptionsButton}>
                    <img src={subscriptionsIcon} alt="subscriptions icon" />Subscriptions
                </button>
            </Link>

            <Link to={"/history"}>
                <button id={selectedPage.page == PageOptions.History ? styles.selected : ""} className={styles.historyButton}>
                    <img src={historyIcon} alt="history icon" />History
                </button>
            </Link>

            <Link to={"/playlists"}>
                <button id={selectedPage.page == PageOptions.Playlists ? styles.selected : ""} className={styles.playListsButton}>
                    <img src={playlistsIcon} alt="playlists icon" />Playlists
                </button>
            </Link>

            <Link to={"/my-videos"}>
                <button id={selectedPage.page == PageOptions.MyVideos ? styles.selected : ""} className={styles.myVideosButton}>
                    <img src={videosIcon} alt="my videos icon" />My Videos
                </button>
            </Link>
        </div>
    );

}

export default Menu;