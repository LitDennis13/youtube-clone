import styles from "./PageNotFoundPageStyles.module.css";

function PageNotFoundPage() {

    return <div className={styles.main}>
        <div className={styles.notFoundBox}>
            <h1>Page Not Found</h1>
        </div>
    </div>;
}

export default PageNotFoundPage;