import { useEffect } from "react";
import { Link } from "react-router-dom";

import { PageOptions } from "../../types";
import { UserLoggedInStore, SelectedPageStore } from "../../store";

import styles from "./MyVideosPage.module.css";
import Globalstyles from "../../GlobalStyles/GlobalStyles.module.css";
import NavigationBarStyles from "../NavigationBar/NavigationBarStyles.module.css";

import accountCircleBlue from "../../images/account circle blue.svg";

function UploadVideoPage() {
    const userLoggedIn = UserLoggedInStore((state) => state.value);
    const selectedPage = SelectedPageStore((state) => state.value);
    
    useEffect(() => {
        selectedPage.setSelectedPage(PageOptions.MyVideos);
    }, []);

    return <>
        {(userLoggedIn.data ? 
        <div className={styles.LoggedInMain}>
            
        </div>    
        : 
        <div className={Globalstyles.notLoggedInMain}>
            <div className={Globalstyles.signInBox}>
                <h1>Sign in to see your Videos</h1>
                <Link to={"/signin"} className={Globalstyles.signInButtonLink}>
                    <button className={NavigationBarStyles.signInButton}>
                        <img src={accountCircleBlue} alt="Account circle" />
                        Sign In
                    </button>
                </Link>

            </div>
        </div>
    )}</>;
}

export default UploadVideoPage;