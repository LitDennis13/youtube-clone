import { useEffect } from "react";
import { Link } from "react-router-dom";

import { PageOptions } from "../../types";
import { UserLoggedInStore, SelectedPageStore } from "../../store";

import styles from "./HomePageStyles.module.css";
import Globalstyles from "../../GlobalStyles/GlobalStyles.module.css";
import NavigationBarStyles from "../NavigationBar/NavigationBarStyles.module.css";

import accountCircleBlue from "../../images/account circle blue.svg";

function HomePage() {
    const userLoggedIn = UserLoggedInStore((state) => state.value);
    const selectedPage = SelectedPageStore((state) => state.value);
    
    useEffect(() => {
        selectedPage.setSelectedPage(PageOptions.Home);
    }, []);

    return <>
        {(userLoggedIn.data ? 
        <div className={styles.LoggedInHome}>
            
        </div>    
        : 
        <div className={Globalstyles.notLoggedInMain}>
            <div className={Globalstyles.signInBox}>
                <h1>Sign in to get your Video feed</h1>
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

export default HomePage;